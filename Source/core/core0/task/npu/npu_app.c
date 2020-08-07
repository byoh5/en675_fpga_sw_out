
#include <stdint.h>
#include <string.h>
#include "dev.h"

#include "asm.h"
#include "rv_utils.h"
#include "encoding.h"

#include "npu.h"
#include "./network/npu_cmd.h"
#include "./network/quantized_network.h"
#include "enx_freertos.h"

npu_t npu_instance;
unsigned long prev_cycles = 0;
unsigned long elapsed_cycles = 0;
unsigned int  trap_id = -1;


typedef struct {
    #define MAX_CYCLE_REPORT 4096
    unsigned int  cnt;
    struct {
        unsigned long npu[MAX_CYCLE_REPORT];
        unsigned int  oac[MAX_CYCLE_REPORT];
        unsigned int  dma[MAX_CYCLE_REPORT];
    } cycle;
} npu_cycle_t;

npu_cycle_t cycle_report;

unsigned long read_cycles(void)
{
    unsigned long cycles;
    asm volatile ("rdcycle %0" : "=r" (cycles));
    return cycles;
}

void init_cycle(void)
{
    int i;
    for(i = 0; i < MAX_CYCLE_REPORT; i++) {
        cycle_report.cycle.npu[i] = 0;
        cycle_report.cycle.oac[i] = 0;
        cycle_report.cycle.dma[i] = 0;
    }

    cycle_report.cnt = 0;
}

void push_cycle(void)
{
    if (cycle_report.cnt >= MAX_CYCLE_REPORT) {
        npu_debug("cycle report full\r\n");
        return;
    }

    cycle_report.cycle.npu[cycle_report.cnt] = read_cycles();
    cycle_report.cycle.oac[cycle_report.cnt] = NPU_READ_REG(ADDR_NPU_PERF_CNT_OACT);
    cycle_report.cycle.dma[cycle_report.cnt] = NPU_READ_REG(ADDR_NPU_PERF_CNT_DMA);
    cycle_report.cnt++;
}

void print_cycle(void)
{
    int i;
    unsigned long elap_npu, prev_npu, diff_npu;
    unsigned int  elap_oac, prev_oac, diff_oac;
    unsigned int  elap_dma, prev_dma, diff_dma;

    unsigned long base_npu = cycle_report.cycle.npu[0];
    unsigned int  base_oac = cycle_report.cycle.oac[0];
    unsigned int  base_dma = cycle_report.cycle.dma[0];

    prev_npu = base_npu;
    prev_oac = base_oac;
    prev_dma = base_dma;
    npu_debug("[NPU cycles Report] Layer total, OACT busy, DMA busy\r\n");
    for(i = 1; i < cycle_report.cnt; i++) {
        elap_npu = (cycle_report.cycle.npu[i] - base_npu);
        elap_oac = (cycle_report.cycle.oac[i] - base_oac);
        elap_dma = (cycle_report.cycle.dma[i] - base_dma);

        diff_npu = (cycle_report.cycle.npu[i] - prev_npu);
        diff_oac = (cycle_report.cycle.oac[i] - prev_oac);
        diff_dma = (cycle_report.cycle.dma[i] - prev_dma);

        prev_npu = cycle_report.cycle.npu[i];
        prev_oac = cycle_report.cycle.oac[i];
        prev_dma = cycle_report.cycle.dma[i];

        npu_debug("%8lu, %8lu, %8lu, %8lu, %8lu, %8lu\r\n",
                  diff_npu, elap_npu, diff_oac, elap_oac, diff_dma, elap_dma);
    }
    npu_debug("[NPU cycles Report] Done\r\n");
}

int npu_pic_done = 0;

// GDB break point
void wait_ready();

/* NPU APIs */
npu_t* npu_get_instance()
{
    return &npu_instance;
}

uint8_t* frm_buf_0 = (uint8_t*)0x0;
uint8_t* frm_buf_1 = (uint8_t*)0x0;
uint8_t* frm_buf_2 = (uint8_t*)0x0;
uint8_t* frm_buf_3 = (uint8_t*)0x0;
uint8_t* frm_buf_4 = (uint8_t*)0x0;
uint8_t* frm_buf_5 = (uint8_t*)0x0;
uint8_t* frm_buf_6 = (uint8_t*)0x0;
uint8_t* frm_buf_7 = (uint8_t*)0x0;

uint8_t* detector_work_buf = (uint8_t*)NPU_DATA_POST_BUF;

void npu_init(npu_t* npu_inst)
{
    unsigned int data;

    npu_inst->command_num = 0;
    npu_inst->command_curr = 0;
    npu_inst->command_buf = NULL;

    NPU_WRITE_REG(ADDR_NPU_CONTROL, NPU_CTRL_CMD_SRC|NPU_CTRL_RESET);
    NPU_WRITE_REG(ADDR_NPU_CONTROL, NPU_CTRL_CMD_SRC|NPU_CTRL_RESET);
    NPU_WRITE_REG(ADDR_NPU_CONTROL, NPU_CTRL_RESET);

    //NPU_WRITE_REG(ADDR_NPU_STATUS, 0x0);
    //NPU_WRITE_REG(ADDR_NPU_APB_COMMAND, 0x0);
    //NPU_WRITE_REG(ADDR_NPU_IRQ_REASON, 0x0);


    data = NPU_IRQ_TRAP;
    NPU_WRITE_REG(ADDR_NPU_IRQ_ENABLE, data); 
    NPU_WRITE_REG(ADDR_NPU_IRQ_MASK, data);
    //NPU_WRITE_REG(ADDR_NPU_IRQ_CLEAR, 0x0);

    data =  0x000 << 20;    //R_CB   0/128
    data += 0x080 << 10;    //R_Y  128/128
    data += 0x0c5 << 0;     //R_CR 197/128 
    NPU_WRITE_REG(ADDR_NPU_COLOR_CONV_0, data);

    data =  0x3e9 << 20;    //G_CB -23/128
    data += 0x080 << 10;    //G_Ya 128/128
    data += 0x3c5 << 0;     //G_CR -59/128
    NPU_WRITE_REG(ADDR_NPU_COLOR_CONV_1, data);

    data =  0x0e8 << 20;    //B_CBa 232/128
    data += 0x080 << 10;    //B_Y   128/128
    data += 0x000 << 0;     //B_CR    0/128
    NPU_WRITE_REG(ADDR_NPU_COLOR_CONV_2, data);

    data =  0x2bb << 20;    //R_BIAS - 128 : -325
    data += 0x3d2 << 10;    //G_BIAS - 128 :  -46
    data += 0x298 << 0;     //B_BIAS - 128 : -360
    NPU_WRITE_REG(ADDR_NPU_COLOR_CONV_BIAS, data);

    NPU_WRITE_REG(ADDR_NPU_PERF_CNT_DMA, 0);
    NPU_WRITE_REG(ADDR_NPU_PERF_CNT_OACT, 0);

}


void npu_set_buf(npu_t* npu_inst, uint8_t* fbb_base[8])
{
    int i;
    npu_reg_t *npu_fb_reg = ADDR_NPU_BASE_ADDR0;
    npu_inst->ext_cmd_base = 0;

    for (i=0; i<8; i++) {
        unsigned int frm_base;
        frm_base = (unsigned long)fbb_base[i];
        npu_inst->ext_fbb_base[i] = fbb_base[i];
        NPU_WRITE_REG(npu_fb_reg, frm_base);
        npu_fb_reg++;
    }

    npu_fb_reg = ADDR_NPU_BASE_ADDR0;
    for (i=0; i<8; i++) {
        NPU_READ_REG(npu_fb_reg);
        npu_fb_reg++;
    }
}


void npu_interrupt_handler(void)
{
    unsigned int reason;
    unsigned int reason_clear;

    reason = NPU_READ_REG(ADDR_NPU_IRQ_REASON);

    if (reason & NPU_IRQ_FULL_EMPTY) {
        reason_clear = NPU_IRQ_FULL_EMPTY;
        load_cmd(FEED_CMD_FULL);
    }
    else {
        unsigned long cycles;
        unsigned int oact_busy_cnt;
        unsigned int dma_busy_cnt;
        unsigned int cmd_cnt;
        unsigned int status;
        reason_clear = NPU_IRQ_TRAP;
        // wait_ready for gdb break point
        
        NPU_READ_REG(ADDR_NPU_CMD_CNT);
        NPU_READ_REG(ADDR_NPU_STATUS);
        NPU_WRITE_REG(ADDR_NPU_IRQ_REASON, reason_clear);
        NPU_WRITE_REG(ADDR_NPU_IRQ_CLEAR, 1);
        
        push_cycle();

        oact_busy_cnt = NPU_READ_REG(ADDR_NPU_PERF_CNT_OACT);

        NPU_WRITE_REG(ADDR_NPU_CONTROL, NPU_CTRL_RUN | NPU_CTRL_CMD_SRC);

        npu_pic_done = 1;

        return;
    }

    NPU_WRITE_REG(ADDR_NPU_IRQ_REASON, reason_clear);
    NPU_WRITE_REG(ADDR_NPU_IRQ_CLEAR, 1);
}


void npu_run_pic(npu_t* npu_inst)
{
#ifdef NPU_DEBUG
    int wait_time_out = 5000000;
    int status_print_freq = 100;
    int loop_cnt;
#endif
    unsigned int data;

    // NPU command fifo reset
    NPU_WRITE_REG(ADDR_NPU_CONTROL, NPU_CTRL_CMD_SRC|NPU_CTRL_RESET);
    NPU_WRITE_REG(ADDR_NPU_CONTROL, NPU_CTRL_RESET);

    // APB command for load_description
    NPU_WRITE_REG(ADDR_NPU_APB_COMMAND, 
        (NPU_OPCODE_WR_REG << 28) + (0 << 24) + ((4 - 1) << 16) + ((0x004) << 0));
    data = (unsigned long)npu_inst->ext_cmd_base;
    NPU_WRITE_REG(ADDR_NPU_APB_COMMAND, data);
    // [31:29] : reserved
    // [28:16] : ibuf_addr
    // [15:14] : ibuf_bank
    // [13   ] : csc_on
    // [12:11] : reserved
    // [10: 8] : base_buf_idx
    // [ 7: 6] : reserved
    // [ 5: 4] : mode
    // [ 3   ] : reserved
    // [ 2: 0] : cmd
    data = (0<< 8) + NPU_DMA_LOAD_DESC;
    NPU_WRITE_REG(ADDR_NPU_APB_COMMAND, data);
    // offset_jump
    NPU_WRITE_REG(ADDR_NPU_APB_COMMAND, 0x0);
    // [31:20] num_chunk_m1
    // [19   ] reserved
    // [18: 0] sz_chunk
    NPU_WRITE_REG(ADDR_NPU_APB_COMMAND, 128*4);
    NPU_WRITE_REG(ADDR_NPU_APB_COMMAND, (NPU_OPCODE_RUN << 28) + (1 << 24) + (1 << 16) + (0x000 << 0));

    NPU_WRITE_REG(ADDR_NPU_CONTROL, NPU_CTRL_RUN | NPU_CTRL_CMD_SRC);

    do { 
        npu_reg_t int_reason, data;
        data = NPU_READ_REG(ADDR_NPU_IRQ_REASON);
        int_reason = data & 0xFF;
        trap_id = (data >> 24) & 0xFF;

#ifdef NPU_DEBUG
        if (status_print_freq) {
            if ((loop_cnt % status_print_freq) == 0) {
                unsigned int cmd_cnt, status;
                cmd_cnt = NPU_READ_REG(ADDR_NPU_CMD_CNT);
                status = NPU_READ_REG(ADDR_NPU_STATUS);

            }
        }
        loop_cnt++;
#endif

        if (int_reason) {
            npu_interrupt_handler();
        }

        if ((int_reason == NPU_IRQ_TRAP) && (trap_id == 0)) {
            break;
        }

#ifdef NPU_DEBUG
        if (--wait_time_out < 0) {
            do {
                npu_debug("Time out\r\n");
            } while(0);
            break;
        }
#endif
        vTaskDelay(1);
    } while(1);

#ifdef NPU_DEBUG
    {
        unsigned int oact_busy_cnt;
        unsigned int dma_busy_cnt;
        unsigned int cmd_cnt;
        unsigned int status;

        oact_busy_cnt = NPU_READ_REG(ADDR_NPU_PERF_CNT_OACT);
        cmd_cnt = NPU_READ_REG(ADDR_NPU_CMD_CNT);
        status = NPU_READ_REG(ADDR_NPU_STATUS);
        dma_busy_cnt = NPU_READ_REG(ADDR_NPU_PERF_CNT_DMA);
        npu_debug("[NPU DBG] cmd oact dma status: %d %d %d 0x%08x\r\n",
            cmd_cnt, oact_busy_cnt, dma_busy_cnt, status);
    }
#endif
    NPU_READ_REG(ADDR_NPU_CMD_CNT);
    NPU_READ_REG(ADDR_NPU_STATUS);

    NPU_WRITE_REG(ADDR_NPU_CONTROL, 0);

#ifdef NPU_DEBUG
    probe_npu_int_apb_regs();
#endif
}


/* NPU Helpers */
void load_cmd(int num)
{
    int i;
    npu_t* npu_inst = npu_get_instance();
    const unsigned int trap_cmd = 
        (NPU_OPCODE_TRAP << 28) + ((NPU_WAIT_COND_DMA | NPU_WAIT_COND_COMP) << 24);

    unsigned int  cmd_num = npu_inst->command_num;
    unsigned int  cmd_cur = npu_inst->command_curr;
    unsigned int* cmd_buf = &npu_inst->command_buf[cmd_cur];

    int feed_num = NPU_MIN((cmd_num - cmd_cur), num);

    if (feed_num <= 0)
        return;

    for (i = 0; i < feed_num; i++) {
        NPU_WRITE_REG(ADDR_NPU_APB_COMMAND, cmd_buf[i]);
        cmd_cur++;
    }

    npu_inst->command_curr = cmd_cur;

    if (cmd_cur >= cmd_num) {
        NPU_WRITE_REG(ADDR_NPU_APB_COMMAND, trap_cmd);
    }

}






void read_fbb_list(uint8_t* fbb[8]) 
{
    int i;

    if (frm_buf_0 == 0)
        fbb[0] = (uint8_t*)npu_cmd;
    else
        fbb[0] = frm_buf_0;

    if (frm_buf_1 == 0)
        fbb[1] = (uint8_t*)quantized_network;
    else
        fbb[1] = frm_buf_1;

//    fbb[0] = 0x84000000;
//    fbb[1] = 0x84800000;
    fbb[2] = NPU_DATA_ACV_BUF;//frm_buf_2;
    fbb[3] = NPU_DATA_INPUT_BUF;//frm_buf_3;
    fbb[4] = NPU_DATA_OUTPUT_BUF;//frm_buf_4;
    fbb[5] = 0x0;//frm_buf_5;
    fbb[6] = 0x0;//frm_buf_6;
    fbb[7] = 0x0;//frm_buf_7;

    for (i=0; i<8; i++) {
        npu_debug("base reg[%d]: %08x\r\n", i, fbb[i]);
    }
}

/* NPU Apps */
void wait_ready() 
{ 
    //
    NPU_WRITE_REG(ADDR_NPU_PERF_CNT_OACT, 0);
}

void flush_dcache_buf(void* buf, unsigned int buf_size)
{
    ulong sadr = (ulong)buf;
    ulong size = (ulong)buf_size;
    hwflush_dcache_range(sadr, size);
}





void run_npu(void)
{
    // Host need to provide buffer addresses
    uint8_t* fb_base[8];
    uint32_t data;
    
    void *oact_base;
    unsigned int oact_buf_size = 1024*1024;

    npu_t* npu_inst = npu_get_instance();

    write_csr(mstatus, MSTATUS_FS);

    npu_init(npu_inst);


    uint8_t* pact = NPU_DATA_FLAG_BUF;

    *pact = 0;

    do {

    	while(*pact != 1){
    		//printf("wait for Control\n");
    		vTaskDelay(1);
    	}


        wait_ready();

        read_fbb_list(fb_base);

        detector_init(detector_work_buf);

        npu_set_buf(npu_inst, fb_base);

        npu_debug("[NPU DBG] Pic Start\r\n");

        init_cycle();
        push_cycle();

        npu_run_pic(npu_inst);

        print_cycle();

        oact_base = (void*)fb_base[4];

        while(npu_pic_done == 0) {
        	vTaskDelay(1);
        }
        run_post_process(oact_base);

        npu_debug("[NPU DBG] Pic Done\r\n");

        hwflush_dcache_all();

        vTaskDelay(1);

        *pact = 0;					//process done : reset activate flag


    } while(1);

    wait_ready();
}









#define WIDTH 1895  //  1920 : 304 = x : 300
#define HIGHT 1080

char npu_class[21][32] = {"BACKGROUND","aeroplane","bicycle","bird","boat","bottle",
		"bus",
		"car",
		"cat",
		"chair",
		"cow",
		"diningtable",
		"dog",
		"horse",
		"motorbike",
		"person",
		"pottedplant",
		"sheep",
		"sofa",
		"train",
		"tvmonitor" };

//int calcPos(int img_size,int pos, )
char npu_color[21][3] = { {0x52 ,0x5a ,0xf0 }, 	// 1 BACKGROUND  red
						  {255 ,0 ,148 },		// 2 aeroplane   yellow
						  {149 ,43 ,21 },		// 3 bicycle     green
						  {29 ,255 ,107 },		// 4 bird        blue
						  {105 ,212 ,234 },		// 5 boat 		 Magenta
						  {178 ,171 ,0 },		// 6 bottle      Cyan
						  {0x52 ,0x5a ,0xf0 }, 	// 7 bus 		 red
						  {255 ,0 ,148 },		// 8 car 		 yellow
						  {149 ,43 ,21 },		// 9 cat 		 green
						  {29 ,255 ,107 },		// 10 chair 	 blue
						  {105 ,212 ,234 },		// 11 cow 		 Magenta
					      {178 ,171 ,0 },		// 12 diningtable Cyan
						  {0x52 ,0x5a ,0xf0 }, 	// 13 dog 		 red
						  {255 ,0 ,148 },		// 14 horse 	 yellow
						  {149 ,43 ,21 },		// 15 motorbike  green
						  {159 ,82 ,195 },		// 16 person 	 Coral
						  {105 ,212 ,234 },		// 17 pottedplant Magenta
						  {178 ,171 ,0 },		// 18 sheep 	 Cyan
						  {0x52 ,0x5a ,0xf0 }, 	// 19 sofa 		 red
						  {255 ,0 ,148 },		// 20 train 	 yellow
						  {149 ,43 ,21 },		// 21 tvmonitor  green
						};

void NPUresult(void)
{

	 uint32_t* num = DETECTION_NUM;
	 uint32_t* data = DETECTION_DATA;

	 uint32_t number=0;
	 int sx,ex,sy,ey;
	 int scr;
	 int cls;

	 number = *num;


	 printf("[OBJECT] : %d \n",number);

	 BOX_ERASE_ALL(AI);
	 FontClrAll(0,0);

	 for (int i=0; i< number ; i++){
		sx = *(data+(i*6));
		ex = *(data+(i*6)+1);
		sy = *(data+(i*6)+2);
		ey = *(data+(i*6)+3);
		scr = *(data+(i*6)+4);
		cls = *(data+(i*6)+5);

		if(sx<0) sx=0;
		else 	 sx = sx*WIDTH/256;
		if(ex<0) ex=0;
		else 	 ex = ex*WIDTH/256;
		if(sy<0) sy=0;
		else 	 sy = sy*HIGHT/256;
		if(ey<0) ey=0;
		else 	 ey = ey*HIGHT/256;


		printf("RESULT : x_min: %d, x_max: %d, y_min: %d, y_max: %d, score: %d, class: %s\n",
						sx,
						ex,
						sy,
						ey,
						scr*100/256,
						npu_class[cls]);

		int score;
		score = scr*100/256;
		int tone;
		if (score>90) tone = BOX_TONE_50;
		else tone = BOX_TONE_25;


		BOX_DRAW(AI,i,1,tone,npu_color[cls][0],npu_color[cls][1],npu_color[cls][2],sx,sy,ex,ey);
		FontStrEx((sy+ey)/48,((sx+ex)/42)-4, 0, 0,npu_class[cls], strlen(npu_class[cls]));


	 }



}





void run_npu_rtcam(void)
{


    // Host need to provide buffer addresses
    uint8_t* fb_base[8];
    uint32_t data;

    void *oact_base;
    unsigned int oact_buf_size = 1024*1024;

    npu_t* npu_inst = npu_get_instance();

    write_csr(mstatus, MSTATUS_FS);

    npu_init(npu_inst);

    uint32_t* num = DETECTION_NUM;
    *num = 0;

    BYTE * src =   IMGAE_BUF;
    BYTE * dat =	NPU_DATA_INPUT_BUF;

    do {

    	BDmaMemCpy_rtos(0, dat, src, 304*300*3);

//    	hwflush_dcache_range_all();			//for update image

        wait_ready();

        read_fbb_list(fb_base);

        detector_init(detector_work_buf);

        npu_set_buf(npu_inst, fb_base);

        npu_debug("[NPU DBG] Pic Start\r\n");

        init_cycle();
        push_cycle();

        npu_run_pic(npu_inst);

        print_cycle();

        oact_base = (void*)fb_base[4];

        while(npu_pic_done == 0) {
        	vTaskDelay(1);
        }
        hwflush_dcache_all();

        run_post_process(oact_base);

        npu_debug("[NPU DBG] Pic Done\r\n");

        NPUresult();

        vTaskDelay(1);



    } while(1);

    wait_ready();
}
