#ifndef _NPU_H
#define _NPU_H

#include <stdint.h>
#include "dev.h"

#define NPU_DEBUG
#ifdef NPU_DEBUG
#   define npu_debug(...)  do {_printf(__VA_ARGS__);} while(0)
#else
#   define npu_debug(...)  do {} while(0)
#endif

#define NPU_MIN(a,b) (((a)<(b))?(a):(b))
#define NPU_MAX(a,b) (((a)>(b))?(a):(b))

typedef  volatile unsigned int npu_reg_t;

#define NPU_APB_BASE		      (0x46300000)
/* ADDR_NPU_IRQ_CONTROL
    [0] : run
    [1] : reset */
#define ADDR_NPU_CONTROL          ((npu_reg_t *)(NPU_APB_BASE + 0x00))
#define ADDR_NPU_STATUS           ((npu_reg_t *)(NPU_APB_BASE + 0x04))
#define ADDR_NPU_APB_COMMAND      ((npu_reg_t *)(NPU_APB_BASE + 0x08))
#define ADDR_NPU_ID_CODE        ((npu_reg_t *)(NPU_APB_BASE + 0x0C))
/* ADDR_NPU_IRQ_XXX
    [0] : full_empty  
    [1] : half_empty  
    [2] : trap  */
#define ADDR_NPU_IRQ_REASON       ((npu_reg_t *)(NPU_APB_BASE + 0x10))
#define ADDR_NPU_IRQ_ENABLE       ((npu_reg_t *)(NPU_APB_BASE + 0x14))
#define ADDR_NPU_IRQ_MASK         ((npu_reg_t *)(NPU_APB_BASE + 0x18))
#define ADDR_NPU_IRQ_CLEAR        ((npu_reg_t *)(NPU_APB_BASE + 0x1C))
#define ADDR_NPU_COLOR_CONV_0     ((npu_reg_t *)(NPU_APB_BASE + 0x20))
#define ADDR_NPU_COLOR_CONV_1     ((npu_reg_t *)(NPU_APB_BASE + 0x24))
#define ADDR_NPU_COLOR_CONV_2     ((npu_reg_t *)(NPU_APB_BASE + 0x28))
#define ADDR_NPU_COLOR_CONV_BIAS  ((npu_reg_t *)(NPU_APB_BASE + 0x2C))

#define ADDR_NPU_READ_INT_REG     ((npu_reg_t *)(NPU_APB_BASE + 0x30))
#define ADDR_NPU_INT_REG_RDATA    ((npu_reg_t *)(NPU_APB_BASE + 0x34))
#define ADDR_NPU_CMD_CNT          ((npu_reg_t *)(NPU_APB_BASE + 0x38))

#define ADDR_NPU_BASE_ADDR0       ((npu_reg_t *)(NPU_APB_BASE + 0x40))
#define ADDR_NPU_BASE_ADDR1       ((npu_reg_t *)(NPU_APB_BASE + 0x44))
#define ADDR_NPU_BASE_ADDR2       ((npu_reg_t *)(NPU_APB_BASE + 0x48))
#define ADDR_NPU_BASE_ADDR3       ((npu_reg_t *)(NPU_APB_BASE + 0x4C))
#define ADDR_NPU_BASE_ADDR4       ((npu_reg_t *)(NPU_APB_BASE + 0x50))
#define ADDR_NPU_BASE_ADDR5       ((npu_reg_t *)(NPU_APB_BASE + 0x54))
#define ADDR_NPU_BASE_ADDR6       ((npu_reg_t *)(NPU_APB_BASE + 0x58))
#define ADDR_NPU_BASE_ADDR7       ((npu_reg_t *)(NPU_APB_BASE + 0x5C))

#define ADDR_NPU_PERF_CNT_DMA     ((npu_reg_t *)(NPU_APB_BASE + 0x60))
#define ADDR_NPU_PERF_CNT_OACT    ((npu_reg_t *)(NPU_APB_BASE + 0x64))
#define ADDR_NPU_PERF_AXI_CONF    ((npu_reg_t *)(NPU_APB_BASE + 0x70))

#ifdef DEBUG_NPU_REG
#   define NPU_READ_REG(ADDR)        ({npu_reg_t val; val = *ADDR; \
	                                npu_debug("RD_APB [%08x]=%08x\r\n", ADDR, val); \
                                    val;})
#   define NPU_WRITE_REG(ADDR, DATA) ({ (*ADDR=(DATA)); \
	                                npu_debug("WR_APB [%08x]=%08x\r\n", ADDR, DATA);})
#else
#   define NPU_READ_REG(ADDR)        (*ADDR)
#   define NPU_WRITE_REG(ADDR, DATA) (*ADDR=(DATA))
#endif

enum {
    NPU_CTRL_RUN        = 0x1,
    NPU_CTRL_RESET      = 0x2,
    NPU_CTRL_CMD_SRC    = 0x4,
};

enum {
    NPU_IRQ_FULL_EMPTY  = 0x1,
    NPU_IRQ_TRAP        = 0x4,
};

enum {
    NPU_OPCODE_NOP      = 0x0,
    NPU_OPCODE_RUN      = 0x1,
    NPU_OPCODE_WR_REG   = 0x2,
    NPU_OPCODE_TRAP     = 0x3,
};

enum {
    NPU_WAIT_COND_DMA   = 0x1,
    NPU_WAIT_COND_COMP  = 0x2,
};

enum {
    NPU_DMA_LOAD_W      = 0x0,
    NPU_DMA_LOAD_A      = 0x2,
    NPU_DMA_SAVE_A      = 0x3,
    NPU_DMA_LOAD_DESC   = 0x4,
};

//  Internal APB address map
//  |addr[10:8] : master |
//  | 0         : DMA    |
//  | 1         : MM     |
//  | 2         : DW     |
//  | 3         : MISC   |
//  | 4         : ACT    |

#define ADDR_NPU_INT_APB_DMA    (0x000)
#define SIZE_NPU_INT_APB_DMA    (5)
#define ADDR_NPU_INT_APB_MM     (0x100)
#define SIZE_NPU_INT_APB_MM     (5)
#define ADDR_NPU_INT_APB_DW     (0x200)
#define SIZE_NPU_INT_APB_DW     (5)
#define ADDR_NPU_INT_APB_MISC   (0x300)
#define SIZE_NPU_INT_APB_MISC   (5)
#define ADDR_NPU_INT_APB_ACT    (0x400)
#define SIZE_NPU_INT_APB_ACT    (5)
#define RDATA_NOT_READY         (0xFFFFFFFF)
#define INVALID_ADDR_ACCESS     (0xBAB0BAB0)

#define CMD_QUE_NUM             (32)
#define FEED_CMD_FULL           (32)
#define FEED_CMD_HALF           (15)

void probe_npu_int_apb_regs(void);

// npu
typedef struct {
    unsigned int command_num;
    unsigned int command_curr;
    unsigned int* command_buf;

    uint8_t* ext_cmd_base;
    uint8_t* ext_fbb_base[8];
} npu_t;




#define NPU_DATA_ACT_SIZE  	 0x1000000
#define NPU_DATA_POST_SIZE    0x550000  //0x550000
#define NPU_DATA_INPUT_SIZE    0x50000  //0x50000
#define NPU_DATA_OUTPUT_SIZE   0x40000 //0x20000
#define NPU_DATA_FLAG_SIZE     0x10000 //0x10000

#define NPU_DATA_BASE  		0x95000000
#define NPU_DATA_ACV_BUF 	NPU_DATA_BASE
#define NPU_DATA_POST_BUF 	NPU_DATA_ACV_BUF + NPU_DATA_ACT_SIZE
#define NPU_DATA_INPUT_BUF  NPU_DATA_POST_BUF + NPU_DATA_POST_SIZE
#define NPU_DATA_OUTPUT_BUF NPU_DATA_INPUT_BUF + NPU_DATA_INPUT_SIZE
#define NPU_DATA_FLAG_BUF   NPU_DATA_OUTPUT_BUF + NPU_DATA_OUTPUT_SIZE
#define DETECTION_NUM 		NPU_DATA_FLAG_BUF + 4
#define DETECTION_DATA 		NPU_DATA_FLAG_BUF + 8

#define IMGAE_BUF 0x94000000

// api
npu_t* npu_get_instance();
void npu_init(npu_t* npu_inst);
void npu_set_buf(npu_t* npu_inst, uint8_t* fbb_base[8]);
void npu_interrupt_handler(void);
void npu_run_pic(npu_t* npu_inst);

// helper
void load_cmd(int num);

// app
void run_npu(void);
void run_npu_rtcam(void);
void run_post_process(void *oact_base);

#endif /*_NPU_H */
