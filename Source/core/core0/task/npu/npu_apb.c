
#include "npu.h"
#include "dev.h"
#include <stdint.h>
#include <string.h>

#define TEST_PAT 0xFFFFFFFF

npu_reg_t* apb_regs[] = {
    ADDR_NPU_CONTROL,
    ADDR_NPU_STATUS,
    ADDR_NPU_APB_COMMAND,
    ADDR_NPU_ID_CODE,
    ADDR_NPU_IRQ_REASON,
    ADDR_NPU_IRQ_ENABLE,
    ADDR_NPU_IRQ_MASK,
    ADDR_NPU_IRQ_CLEAR,
    ADDR_NPU_COLOR_CONV_0,
    ADDR_NPU_COLOR_CONV_1,
    ADDR_NPU_COLOR_CONV_2,
    ADDR_NPU_COLOR_CONV_BIAS,
    ADDR_NPU_READ_INT_REG,
    ADDR_NPU_INT_REG_RDATA,
};


unsigned int npu_read_int_reg(unsigned int addr)
{
    unsigned int data;
    npu_reg_t* rdata_reg = ADDR_NPU_INT_REG_RDATA;
    npu_reg_t* raddr_reg = ADDR_NPU_READ_INT_REG;
    NPU_WRITE_REG(raddr_reg, addr & 0x7FC);

    do {
        data = NPU_READ_REG(rdata_reg);
    } while(data == RDATA_NOT_READY);

    return data;
}


void probe_npu_int_apb_regs(void)
{
   unsigned int i, addr, data;
   unsigned int int_reg_addr, len;

   // DMA
   int_reg_addr = ADDR_NPU_INT_APB_DMA;
   len = SIZE_NPU_INT_APB_DMA;
   for (i = 0; i < len; i++) {
       addr = int_reg_addr + (i << 2);
       data = npu_read_int_reg(addr);
   //    _printf("  READ I_APB[%08x]:%08x\r\n", addr, data);
   }

   // MM
   int_reg_addr = ADDR_NPU_INT_APB_MM;
   len = SIZE_NPU_INT_APB_MM;
   for (i = 0; i < len; i++) {
       addr = int_reg_addr + (i << 2);
       data = npu_read_int_reg(addr);
   //    _printf("  READ I_APB[%03x]:%08x\r\n", addr, data);
   }

   // DM
   int_reg_addr = ADDR_NPU_INT_APB_DW;
   len = SIZE_NPU_INT_APB_DW;
   for (i = 0; i < len; i++) {
       addr = int_reg_addr + (i << 2);
       data = npu_read_int_reg(addr);
    //   _printf("  READ I_APB[%03x]:%08x\r\n", addr, data);
   }

   // ACT
   int_reg_addr = ADDR_NPU_INT_APB_ACT;
   len = SIZE_NPU_INT_APB_ACT;
   for (i = 0; i < len; i++) {
       addr = int_reg_addr + (i << 2);
       data = npu_read_int_reg(addr);
   //   _printf("  READ I_APB[%03x]:%08x\r\n", addr, data);
   }

}



void test_npu_ext_apb_regs(void)
{
    int i;
    int num_regs = sizeof(apb_regs)/sizeof(npu_reg_t*);

    for(i = 0; i < num_regs - 2; i++){
        NPU_WRITE_REG(apb_regs[i], 0);
        NPU_READ_REG(apb_regs[i]);
    }
}

