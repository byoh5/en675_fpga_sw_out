#include "dev.h"
#include "sfls_model.h"

SFLScontrol *sfls_master = NULL;

void SflsInit(void)
{
	UINT nQPIFlag = 0;

	while (!SFLS_ID_VAL);

	SflsGetinfo();
	if (sfls_master == NULL) {
		return;
	}

	//SFLS_IO_RXEDGE = 1;
	//SFLS_IO_TXEDGE = 1;

#if 1 // bootloader only
#if 1
	UINT sfls_clk = 50000000;
	SflsSetClk(sfls_clk);
#else
	SflsSetClkdiv(0xf);
#endif

	if (sfls_master->func_init_1) {
		sfls_master->func_init_1();
	}

	if (sfls_master->use_4b == 1) {
		SflsEnterQE();
	}

	if (sfls_master->use_4b == 1) {
		SflsEnter4B();
	}

	if (sfls_master->use_qpi == 1) {
		sfls_master->is_qpi = ENX_NO;
		SflsEnterQPI();
		if (sfls_master->is_qpi == ENX_YES) {
			nQPIFlag = 1;
		}
	}

	SFLS_BUS_RD_CMD_MODE = sfls_master->ior_cmd;
	SFLS_BUS_RD_ADR_MODE = sfls_master->ior_adr;
	SFLS_BUS_RD_DAT_MODE = sfls_master->ior_dat;
	SFLS_BUS_WR_CMD_MODE = sfls_master->iow_cmd;
	SFLS_BUS_WR_ADR_MODE = sfls_master->iow_adr;
	SFLS_BUS_WR_DAT_MODE = sfls_master->iow_dat;
	SFLS_BUS_WREN_CMD_MODE = sfls_master->iowe_cmd;
	SFLS_BUS_RDREG_CMD_MODE = sfls_master->iors_cmd;
	SFLS_BUS_RDREG_DAT_MODE = sfls_master->iors_dat;

	SFLS_BUS_CMD_RD = sfls_master->cmd_read;
	SFLS_BUS_CMD_WR = sfls_master->cmd_page_program;
	SFLS_BUS_CMD_WREN = sfls_master->cmd_write_enable;
	SFLS_BUS_CMD_RDREG = sfls_master->cmd_read_status;

#if (EN675_SINGLE==0)
	if (sfls_master->gap) {
		SFLS_BUS_GAP_EN	= 1;
		SFLS_BUS_GAP = sfls_master->gap - 1;
	} else {
		SFLS_BUS_GAP_EN	= 0;
		SFLS_BUS_GAP = 0;
	}
	SFLS_IO_RDLTC = sfls_master->rdltc;
#else
#if EN675_SINGLE_SFLS_NEW
	if (sfls_master->mode_en) {
		SFLS_BUS_MODE_EN = 1;
		SFLS_BUS_MODE_VALUE = sfls_master->mode_val;
	} else {
		SFLS_BUS_MODE_EN = 0;
		SFLS_BUS_MODE_VALUE = 0;
	}
#endif
	if (sfls_master->gap) {
		SFLS_BUS_GAP = sfls_master->gap;
	} else {
		SFLS_BUS_GAP = 0;
	}
	SFLS_BUS_RDLTC = sfls_master->rdltc;
#endif

	if (nQPIFlag == 1) {
		SFLS_USRBUS_REQ = 1;
		while (SFLS_USRBUS_REQ);
	} else {
		SFLS_BUS_REQ = 1;
		while (SFLS_BUS_REQ);
	}

	SFLS_USR_CMD_MODE = 0;
	SFLS_USR_ADR_MODE = 0;
	SFLS_USR_DAT_MODE = 0;
	SFLS_USR_RDREG_CMD_MODE = sfls_master->iors_cmd;
	SFLS_USR_RDREG_DAT_MODE = sfls_master->iors_dat;
	SFLS_USR_RDLTC = sfls_master->rdltc;

	if (sfls_master->func_init_2) {
		sfls_master->func_init_2();
	}
#endif
	ENX_DEBUGF(DBG_SFLS_STATUS, "SFLS Init - %s%uHz%s\n", TTY_COLOR_GREEN, SflsGetClk(), TTY_COLOR_RESET);
}

////////////////////////////////////////////////////////////////////////////////
//
// QSPI-NOR clock settings
//
////////////////////////////////////////////////////////////////////////////////

void SflsSetClkdiv(UINT Clkdiv)
{
	SFLS_IO_CLKDIV = Clkdiv;
}

UINT SflsGetClkdiv(void)
{
	return SFLS_IO_CLKDIV;
}

void SflsSetClk(UINT Speed_Hz)
{
	UINT u32Cal = (APB_FREQ / (Speed_Hz * 2)) - 1;
	if (u32Cal < 256) {
		SFLS_IO_CLKDIV = u32Cal;
	} else {
		if (u32Cal == 0xFFFFFFFF) {
			SFLS_IO_CLKDIV = 0;
		} else {
			SFLS_IO_CLKDIV = 255;
		}
		ENX_DEBUGF(DBG_SFLS_WARNING, "SFLS Clk %s.(%u/%u)\n", SFLS_IO_CLKDIV ? "Min" : "Max", u32Cal, SFLS_IO_CLKDIV);
	}
}

UINT SflsGetClk(void)
{
	ENX_DEBUGF(DBG_SFLS_LOG, "SFLS Clk %uHz(%u)\n", APB_FREQ / ((SFLS_IO_CLKDIV + 1) * 2), SFLS_IO_CLKDIV);
	return APB_FREQ / ((SFLS_IO_CLKDIV + 1) * 2);
}

////////////////////////////////////////////////////////////////////////////////
//
// QSPI-NOR get information
//
////////////////////////////////////////////////////////////////////////////////

UINT SflsGetinfo(void)
{
	printf("%c: SFLS_ID Get[0x%08X]\n", SFLS_ID_VAL == 1 ? 'O' : 'X', SFLS_ID);
	BYTE u8Manid = SFLS_ID >> 16 & 0xff;
	BYTE u8Type = SFLS_ID >> 8 & 0xff;
	BYTE u8Capa = SFLS_ID & 0xff;
	SFLS_SIZE = 1 << u8Capa;
	printf("ID(%02X) Type(%02X) Capa(%02X/%ubyte) - ", u8Manid, u8Type, u8Capa, SFLS_SIZE);

	switch (u8Manid) {
	case 0x1C: // EON
		sfls_master = SflsModelEON(u8Type, u8Capa);
		break;
	case 0x20: // Micron
		sfls_master = SflsModelMicron(u8Type, u8Capa);
		break;
	case 0x9D: // ISSI
		sfls_master = SflsModelISSI(u8Type, u8Capa);
		break;
	case 0x9F: // Macronix (3.3v)
	case 0xC2: // Macronix (1.8v)
		sfls_master = SflsModelMacronix(u8Type, u8Capa);
		break;
	case 0xC8: // GigaDevice
		sfls_master = SflsModelGigaDevice(u8Type, u8Capa);
		break;
	case 0xEF: // Winbond
		sfls_master = SflsModelWinbond(u8Type, u8Capa);
		break;
	case 0xFF:
		printf("SFLS No connection.\n");
		break;
	default:
		printf("SFLS Error.\n");
		//ENX_ASSERT(0);
		break;
	}

	return SFLS_ID;
}

UINT SflsGetSize(void)
{
	if (sfls_master) {
		return sfls_master->size;
	}
	_Rprintf("Error sfls size, default 16MB\n");
	return (16 * 1024 * 1024);
}

UINT SflsGetUsrreq(void)
{
	return SFLS_USR_REQ;
}

////////////////////////////////////////////////////////////////////////////////
//
// QSPI-NOR single command
//
////////////////////////////////////////////////////////////////////////////////

void SflsSingleCommandNoReq(BYTE cmd, UINT CMD_MODE)
{
	SFLS_USR_CMD_MODE = CMD_MODE;
#if (EN675_SINGLE==0)
	SFLS_USR_GAP_EN = 0;
#else
	SFLS_USR_GAP = 0;
#endif
	SFLS_USR_ADR_EN = 0;
	SFLS_USR_RD_EN = 0;
	SFLS_USR_WR_EN = 0;
	SFLS_USR_BUSY_EN = 0;
	SFLS_USR_CMD = cmd;
}

void SflsSingleCommand(BYTE cmd, UINT CMD_MODE)
{
	SflsSingleCommandNoReq(cmd, CMD_MODE);
	SFLS_USR_REQ = 1;
	while (SFLS_USR_REQ);
}

////////////////////////////////////////////////////////////////////////////////
//
// QSPI-NOR command
//
////////////////////////////////////////////////////////////////////////////////

void SflsWriteEnable(void)
{
	if (sfls_master && sfls_master->func_write_enable) {
		_Yprintf("%s: private func\n", __func__);
		sfls_master->func_write_enable();
	} else if (sfls_master->cmd_write_enable != 0) {
		SflsSingleCommandNoReq(sfls_master->cmd_write_enable, sfls_master->is_qpi ? 2 : 0);
		SFLS_USR_REQ = 1;
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Write enable is not supported.\n");
	}
}

void SflsWriteDisable(void)
{
	if (sfls_master && sfls_master->func_write_disable) {
		_Yprintf("%s: private func\n", __func__);
		sfls_master->func_write_disable();
	} else if (sfls_master->cmd_write_disable != 0) {
		SflsSingleCommandNoReq(sfls_master->cmd_write_disable, sfls_master->is_qpi ? 2 : 0);
		SFLS_USR_REQ = 1;
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Write disable is not supported.\n");
	}
}

static void SflsErase(SFLS_ERASE erase_type, UINT addr)
{
	if (sfls_master->is_qpi) {
#if (EN675_SINGLE==0)
		SFLS_USR_RDLTC = SFLS_IO_RDLTC;
#else
		SFLS_USR_RDLTC = SFLS_BUS_RDLTC;
#endif
		SFLS_USR_CMD_MODE = 2;
		SFLS_USR_ADR_MODE = 2;
	} else {
		SFLS_USR_RDLTC = 1;
		SFLS_USR_CMD_MODE = 0;
		SFLS_USR_ADR_MODE = 0;
	}

	if (erase_type == SFLS_E_ALL) {
		SFLS_USR_ADR_EN = 0;
		SFLS_USR_ADR = 0;
	} else {
		SFLS_USR_ADR_EN = 1;
		SFLS_USR_ADR = addr;
	}
#if (EN675_SINGLE==0)
	SFLS_USR_GAP_EN = 0;
#else
	SFLS_USR_GAP = 0;
#endif
	SFLS_USR_RD_EN = 0;
	SFLS_USR_WR_EN = 0;
	SFLS_USR_ADR_EXT = SFLS_BUS_ADR_EXT;
	SFLS_USR_BUSY_EN = 1;
	switch (erase_type) {
	case SFLS_E_ALL:
		SFLS_USR_CMD = sfls_master->cmd_erase_all;
		break;
	case SFLS_E_4K:
		SFLS_USR_CMD = sfls_master->cmd_erase_secter;
		break;
	case SFLS_E_32K:
		SFLS_USR_CMD = sfls_master->cmd_erase_32kbyte;
		break;
	case SFLS_E_64K:
		SFLS_USR_CMD = sfls_master->cmd_erase_64kbyte;
		break;
	}
	SFLS_USR_REQ = 1;
}

void SflsChipErase(ENX_YN sync)
{
	while (SFLS_USR_REQ);
	SflsWriteEnable();

	while (SFLS_USR_REQ);
	if (sfls_master && sfls_master->func_chip_erase) {
		_Yprintf("%s: private func\n", __func__);
		sfls_master->func_chip_erase(0);
	} else {
		SflsErase(SFLS_E_ALL, 0);
	}
	if (sync == ENX_YES) {
		while (SFLS_USR_REQ);
	}
}

void SflsSectErase(UINT addr, ENX_YN sync)
{
	while (SFLS_USR_REQ);
	SflsWriteEnable();

	while (SFLS_USR_REQ);
	if (sfls_master && sfls_master->func_secter_erase) {
		_Yprintf("%s: private func\n", __func__);
		sfls_master->func_secter_erase(addr);
	} else {
		SflsErase(SFLS_E_4K, addr);
	}
	if (sync == ENX_YES) {
		while (SFLS_USR_REQ);
	}
}

void Sfls32KErase(UINT addr, ENX_YN sync)
{
	while (SFLS_USR_REQ);
	SflsWriteEnable();

	while (SFLS_USR_REQ);
	if (sfls_master && sfls_master->func_32k_erase) {
		_Yprintf("%s: private func\n", __func__);
		sfls_master->func_32k_erase(addr);
	} else {
		SflsErase(SFLS_E_32K, addr);
	}
	if (sync == ENX_YES) {
		while (SFLS_USR_REQ);
	}
}

void Sfls64KErase(UINT addr, ENX_YN sync)
{
	while (SFLS_USR_REQ);
	SflsWriteEnable();

	while (SFLS_USR_REQ);
	if (sfls_master && sfls_master->func_64k_erase) {
		_Yprintf("%s: private func\n", __func__);
		sfls_master->func_64k_erase(addr);
	} else {
		SflsErase(SFLS_E_64K, addr);
	}
	if (sync == ENX_YES) {
		while (SFLS_USR_REQ);
	}
}

void SflsWriteStatusCmd(BYTE cmd, BYTE status)
{
	if (sfls_master->is_qpi) {
#if (EN675_SINGLE==0)
		SFLS_USR_RDLTC = SFLS_IO_RDLTC;
#else
		SFLS_USR_RDLTC = SFLS_BUS_RDLTC;
#endif
		SFLS_USR_CMD_MODE = 2;
		SFLS_USR_DAT_MODE = 2;
	} else {
		SFLS_USR_RDLTC = 1;
		SFLS_USR_CMD_MODE = 0;
		SFLS_USR_DAT_MODE = 0;
	}
#if (EN675_SINGLE==0)
	SFLS_USR_GAP_EN = 0;
#else
	SFLS_USR_GAP = 0;
#endif
	SFLS_USR_ADR_EN = 0;
	SFLS_USR_RD_EN = 0;
	SFLS_USR_WR_EN = 1;
	SFLS_USR_BUSY_EN = 1;
	SFLS_USR_CMD = cmd;
	SFLS_USR_LEN = 0;
	SFLS_USR_WRDAT = status << 24;
	SFLS_USR_REQ = 1;
	while (SFLS_USR_REQ);
}

void SflsWriteStatus(BYTE status)
{
	if (sfls_master) {
		SflsWriteEnable();
		while (SFLS_USR_REQ);

		if (sfls_master->func_write_status) {
			_Yprintf("%s: private func\n", __func__);
			sfls_master->func_write_status(status);
		} else if (sfls_master->cmd_write_status != 0) {
			SflsWriteStatusCmd(sfls_master->cmd_write_status, status);
		} else {
			ENX_DEBUGF(DBG_SFLS_WARNING, "Write status is not supported.\n");
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
}

BYTE SflsReadStatusCmd(BYTE cmd)
{
	if (sfls_master->is_qpi) {
#if (EN675_SINGLE==0)
		SFLS_USR_RDLTC = SFLS_IO_RDLTC;
#else
		SFLS_USR_RDLTC = SFLS_BUS_RDLTC;
#endif
		SFLS_USR_CMD_MODE = 2;
		SFLS_USR_DAT_MODE = 2;
	} else {
		SFLS_USR_RDLTC = 1;
		SFLS_USR_CMD_MODE = 0;
		SFLS_USR_DAT_MODE = 0;
	}
#if (EN675_SINGLE==0)
	SFLS_USR_GAP_EN = 0;
#else
	SFLS_USR_GAP = 0;
#endif
	SFLS_USR_ADR_EN = 0;
	SFLS_USR_RD_EN = 1;
	SFLS_USR_WR_EN = 0;
	SFLS_USR_BUSY_EN = 0;
	SFLS_USR_CMD = cmd;
	SFLS_USR_LEN = 0;
	SFLS_USR_REQ = 1;
	while (SFLS_USR_REQ);
	return SFLS_USR_RDDAT >> 24;
}

BYTE SflsReadStatus(void)
{
	BYTE u8status = 0;
	if (sfls_master) {
		if (sfls_master->func_read_status) {
			_Yprintf("%s: private func\n", __func__);
			u8status = sfls_master->func_read_status();
		} else if (sfls_master->cmd_read_status != 0) {
			u8status = SflsReadStatusCmd(sfls_master->cmd_read_status);
		} else {
			ENX_DEBUGF(DBG_SFLS_WARNING, "Read status is not supported.\n");
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
	return u8status;
}

void SflsReadStatusView(BYTE status)
{
	if (sfls_master) {
		if (sfls_master->func_read_status_view) {
#if (DBG_SFLS_STATUS==ENX_DBG_ON)
			_Yprintf("%s: private func\n", __func__);
			sfls_master->func_read_status_view(status);
#endif
		} else {
			ENX_DEBUGF(DBG_SFLS_WARNING, "Read status view is not supported.\n");
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
}

ENX_YN SflsIs4B(void)
{
	if (sfls_master) {
		if (sfls_master->func_is_4b) {
			_Yprintf("%s: private func\n", __func__);
			return sfls_master->func_is_4b();
		} else {
			return sfls_master->is_4b;
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
	return ENX_NO;
}

void SflsEnter4B(void)
{
	if (sfls_master) {
		if (sfls_master->use_4b == 0) {
			ENX_DEBUGF(DBG_SFLS_WARNING, "4byte mode is not used.\n");
		} else {
			if (SflsIs4B() == ENX_NO) {
				if (sfls_master->func_enter_4b) {
					_Yprintf("%s: private func\n", __func__);
					sfls_master->func_enter_4b(ENX_NO);
				} else if (sfls_master->cmd_enter_4b != 0) {
					SflsSingleCommandNoReq(sfls_master->cmd_enter_4b, 0);
				} else {
					ENX_DEBUGF(DBG_SFLS_WARNING, "4byte mode is not supported.\n");
					return;
				}
				SFLS_USR_ADR_EXT = 1;
				SFLS_BUS_ADR_EXT = 1;
				SFLS_USRBUS_REQ = 1;
				while (SFLS_USRBUS_REQ);
				sfls_master->is_4b = ENX_YES;
			} else {
				ENX_DEBUGF(DBG_SFLS_WARNING, "Already enter 4B\n");
			}
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
}

void SflsExit4B(void)
{
	if (sfls_master) {
		if (sfls_master->use_4b == 0) {
			ENX_DEBUGF(DBG_SFLS_WARNING, "4byte mode is not used.\n");
		} else {
			if (SflsIs4B() == ENX_YES) {
				if (sfls_master->func_exit_4b) {
					_Yprintf("%s: private func\n", __func__);
					sfls_master->func_exit_4b(ENX_NO);
				} else if (sfls_master->cmd_exit_4b != 0) {
					SflsSingleCommandNoReq(sfls_master->cmd_exit_4b, 0);
				} else {
					ENX_DEBUGF(DBG_SFLS_WARNING, "4byte mode is not supported.\n");
					return;
				}
				SFLS_USR_ADR_EXT = 0;
				SFLS_BUS_ADR_EXT = 0;
				SFLS_USRBUS_REQ = 1;
				while (SFLS_USRBUS_REQ);
				sfls_master->is_4b = ENX_NO;
			} else {
				ENX_DEBUGF(DBG_SFLS_WARNING, "Already exit 4B\n");
			}
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
}

void SflsEnterQPI(void)
{
	if (sfls_master) {
		if (sfls_master->use_qpi == 0) {
			ENX_DEBUGF(DBG_SFLS_WARNING, "QPI mode is not used.\n");
		} else {
			if (sfls_master->func_is_qpi) {
				if (sfls_master->func_is_qpi() == ENX_NO) {
					if (sfls_master->func_enter_qpi) {
						_Yprintf("%s: private func\n", __func__);
						sfls_master->func_enter_qpi(ENX_NO);
					} else if (sfls_master->cmd_enter_qpi != 0) {
						SflsSingleCommandNoReq(sfls_master->cmd_enter_qpi, 0);
					} else {
						goto not_supported;
					}
					sfls_master->is_qpi = ENX_YES;
				} else {
					ENX_DEBUGF(DBG_SFLS_WARNING, "Already enter QPI\n");
				}
			} else if (sfls_master->cmd_enter_qpi != 0) {
				if (sfls_master->is_qpi == ENX_NO) {
					SflsSingleCommandNoReq(sfls_master->cmd_enter_qpi, 0);
					sfls_master->is_qpi = ENX_YES;
				} else {
					ENX_DEBUGF(DBG_SFLS_WARNING, "Already enter QPI\n");
				}
			} else {
not_supported:
				ENX_DEBUGF(DBG_SFLS_WARNING, "QPI mode is not supported.\n");
			}
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
}

void SflsExitQPI(void)
{
	if (sfls_master) {
		if (sfls_master->use_qpi == 0) {
			ENX_DEBUGF(DBG_SFLS_WARNING, "QPI mode is not used.\n");
		} else {
			if (sfls_master->func_is_qpi) {
				if (sfls_master->func_is_qpi() == ENX_YES) {
					if (sfls_master->func_exit_qpi) {
						_Yprintf("%s: private func\n", __func__);
						sfls_master->func_exit_qpi(ENX_NO);
					} else if (sfls_master->cmd_exit_qpi != 0) {
						SflsSingleCommandNoReq(sfls_master->cmd_exit_qpi, 0);
					} else {
						goto not_supported;
					}
					sfls_master->is_qpi = ENX_NO;
				} else {
					ENX_DEBUGF(DBG_SFLS_WARNING, "Already exit QPI\n");
				}
			} else if (sfls_master->cmd_exit_qpi != 0) {
				if (sfls_master->is_qpi == ENX_YES) {
					SflsSingleCommandNoReq(sfls_master->cmd_exit_qpi, 0);
					sfls_master->is_qpi = ENX_NO;
				} else {
					ENX_DEBUGF(DBG_SFLS_WARNING, "Already exit QPI\n");
				}
			} else {
not_supported:
				ENX_DEBUGF(DBG_SFLS_WARNING, "QPI mode is not supported.\n");
			}
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
}

ENX_YN SflsIsQE(void)
{
	BYTE status = SflsReadStatus();
	if (status & sfls_master->qe_mask) {
		return ENX_YES;
	} else {
		return ENX_NO;
	}
}

void SflsEnterQE(void)
{
	if (sfls_master) {
		if (sfls_master->use_qpi == 0) {
			ENX_DEBUGF(DBG_SFLS_WARNING, "Enter QE is not used.\n");
		} else {
			if (sfls_master->func_enter_qe) {
				_Yprintf("%s: private func\n", __func__);
				sfls_master->func_enter_qe();
			} else if (sfls_master->qe_mask != 0) {
				BYTE status = SflsReadStatus();
				if (!((status & sfls_master->qe_mask) == sfls_master->qe_mask)) {
					status |= sfls_master->qe_mask;
					SflsWriteStatus(status);
				} else {
					ENX_DEBUGF(DBG_SFLS_WARNING, "already enter QE\n");
				}
			} else {
				ENX_DEBUGF(DBG_SFLS_WARNING, "Enter QE is not supported.\n");
			}
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
}

void SflsExitQE(void)
{
	if (sfls_master) {
		if (sfls_master->use_qpi == 0) {
			ENX_DEBUGF(DBG_SFLS_WARNING, "Exit QE is not used.\n");
		} else {
			if (sfls_master->func_exit_qe) {
				_Yprintf("%s: private func\n", __func__);
				sfls_master->func_exit_qe();
			} else if (sfls_master->qe_mask != 0) {
				BYTE status = SflsReadStatus();
				if (status & sfls_master->qe_mask) {
					status &= ~sfls_master->qe_mask;
					SflsWriteStatus(status);
				} else {
					ENX_DEBUGF(DBG_SFLS_WARNING, "already exit QE\n");
				}
			} else {
				ENX_DEBUGF(DBG_SFLS_WARNING, "Exit QE is not supported.\n");
			}
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
}

ENX_YN SflsIsProtection(void)
{
	BYTE status = SflsReadStatus();
	if (status & sfls_master->protection_mask) {
		return ENX_YES;
	} else {
		return ENX_NO;
	}
}

void SflsEnterProtection(void)
{
	if (sfls_master) {
		if (sfls_master->func_enter_protection) {
			_Yprintf("%s: private func\n", __func__);
			sfls_master->func_enter_protection();
		} else if (sfls_master->protection_mask != 0) {
			BYTE status = SflsReadStatus();
			if (!((status & sfls_master->protection_mask) == sfls_master->protection_mask)) {
				status |= sfls_master->protection_mask;
				SflsWriteStatus(status);
			} else {
				ENX_DEBUGF(DBG_SFLS_WARNING, "already enter protection\n");
			}
		} else {
			ENX_DEBUGF(DBG_SFLS_WARNING, "Enter protection is not supported.\n");
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
}

void SflsExitProtection(void)
{
	if (sfls_master) {
		if (sfls_master->func_enter_protection) {
			_Yprintf("%s: private func\n", __func__);
			sfls_master->func_enter_protection();
		} else if (sfls_master->protection_mask != 0) {
			BYTE status = SflsReadStatus();
			if (status & sfls_master->protection_mask) {
				status &= ~sfls_master->protection_mask;
				SflsWriteStatus(status);
			} else {
				ENX_DEBUGF(DBG_SFLS_WARNING, "already exit protection\n");
			}
		} else {
			ENX_DEBUGF(DBG_SFLS_WARNING, "Exit protection is not supported.\n");
		}
	} else {
		ENX_DEBUGF(DBG_SFLS_WARNING, "Not configured.\n");
	}
}

void SflsReadSFDP(BYTE *sfdp_bin)
{
	if (sfls_master && sfls_master->func_read_sfdp) {
		_Yprintf("%s: private func\n", __func__);
		sfls_master->func_read_sfdp(sfdp_bin);
	} else {
		UINT *data = (UINT *)sfdp_bin;
		UINT getVal;

		if (sfls_master->is_qpi) {
#if (EN675_SINGLE==0)
			SFLS_USR_RDLTC = SFLS_IO_RDLTC;
#else
			SFLS_USR_RDLTC = SFLS_BUS_RDLTC;
#endif
			SFLS_USR_CMD_MODE = 2;
			SFLS_USR_ADR_MODE = 2;
			SFLS_USR_DAT_MODE = 2;
		} else {
			SFLS_USR_RDLTC	= 1;
			SFLS_USR_CMD_MODE = 0;
			SFLS_USR_ADR_MODE = 0;
			SFLS_USR_DAT_MODE = 0;
		}
#if (EN675_SINGLE==0)
		SFLS_USR_GAP_EN = SFLS_BUS_GAP_EN;
#endif
		SFLS_USR_GAP = SFLS_BUS_GAP;
		SFLS_USR_ADR_EN = 1;
		SFLS_USR_RD_EN = 1;
		SFLS_USR_WR_EN = 0;
		SFLS_USR_ADR_EXT = 0;
		SFLS_USR_BUSY_EN = 0;
		if (sfls_master->cmd_read_sfdp != 0) {
			SFLS_USR_CMD = sfls_master->cmd_read_sfdp;
		} else {
			SFLS_USR_CMD = 0x5A;
		}
#if (EN675_SINGLE==0)
		SFLS_USR_LEN = 3;
		for (UINT i = 0; i < (256 / 4); i++) {
			SFLS_USR_ADR = i * 4;
			SFLS_USR_REQ = 1;
			while (SFLS_USR_REQ);
			getVal = SFLS_USR_RDDAT;
			data[i] = ENX_HTONL(getVal);
		}
#else
		SFLS_USR_ADR = 0;
		SFLS_USR_LEN = 256 - 1;
		SFLS_USR_REQ = 1;
		while (SFLS_USR_REQ);
		for (UINT i = 0; i < (256 / 4); i++) {
			getVal = SFLS_USR_RDDAT;
			data[i] = ENX_HTONL(getVal);
		}
#endif
	}
}

void SflsViewerSFDP(BYTE *sfdp_bin)
{
	hexDump("SFDP", (BYTE *)sfdp_bin, 256);

	SFLSsfdp_header *sfdphead = (SFLSsfdp_header *)sfdp_bin;
	if (sfdphead->SFDPSignature[0] == 'S' && sfdphead->SFDPSignature[1] == 'F' && sfdphead->SFDPSignature[2] == 'D' && sfdphead->SFDPSignature[3] == 'P') {
		SFLSsfdp *sfdp = (SFLSsfdp *)(sfdp_bin + sfdphead->ParameterTablePointer);

		printf("== %c%c%c%c ==\n", sfdphead->SFDPSignature[0], sfdphead->SFDPSignature[1], sfdphead->SFDPSignature[2], sfdphead->SFDPSignature[3]);
		printf("Parameter Table Length(%u) Pointer(0x%02X)\n", sfdphead->ParameterTableLength, sfdphead->ParameterTablePointer);

		printf("=====================\n");

		printf("Block / Sector Erase sizes : [%u]\n", sfdp->BlockSectorEreaseSize);
		printf("Write Granularity : [%u]\n", sfdp->WriteGranularity);
		printf("Write Enable Instruction Required for Writing to Volatile Status Register : [%u]\n", sfdp->WEIR_WVSR);
		printf("Write Enable Opcode Select for Writing to Volatile Status Register : [%u]\n", sfdp->WEOS_WVSR);
		printf("4 Kilo-Byte Erase Opcode : [0x%02X]\n", sfdp->FourKBEraseOpcode);
		printf("Address Byte : [%u]\n", sfdp->AddrByte);
		printf("Supports Double Transfer Rate (DTR) Clocking : [%u]\n", sfdp->SupDTRClocking);
		printf("SFLS size: %uByte (raw:0x%08X)\n", (sfdp->FlashMemoryDensity + 1) / 8, sfdp->FlashMemoryDensity);

		printf("=====================\n");

		printf("Supports (1-4-4) Fast Read : [%u]\n", sfdp->Sup144FastRead);
		printf("(1-4-4) Fast Read Number of Wait states (dummy clocks) needed before valid output : [%u]\n", sfdp->DummyClock144FR);
		printf("(1-4-4) Fast Read Number of Mode Bits : [%u]\n", sfdp->Modebit144FR);
		printf("(1-4-4) Fast Read Opcode : [0x%02X]\n", sfdp->Op144FR);

		printf("Supports (1-1-4) Fast Read : [%u]\n", sfdp->Sup114FastRead);
		printf("(1-1-4) Fast Read Number of Wait states (dummy clocks) needed before valid output : [%u]\n", sfdp->DummyClock114FR);
		printf("(1-1-4) Fast Read Number of Mode Bits : [%u]\n", sfdp->Modebit114FR);
		printf("(1-1-4) Fast Read Opcode : [0x%02X]\n", sfdp->Op114FR);

		printf("Supports (1-1-2) Fast Read : [%u]\n", sfdp->Sup112FastRead);
		printf("(1-1-2) Fast Read Number of Wait states (dummy clocks) needed before valid output : [%u]\n", sfdp->DummyClock112FR);
		printf("(1-1-2) Fast Read Number of Mode Bits : [%u]\n", sfdp->Modebit112FR);
		printf("(1-1-2) Fast Read Opcode : [0x%02X]\n", sfdp->Op112FR);

		printf("Supports (1-2-2) Fast Read : [%u]\n", sfdp->Sup122FastRead);
		printf("(1-2-2) Fast Read Number of Wait states (dummy clocks) needed before valid output : [%u]\n", sfdp->DummyClock122FR);
		printf("(1-2-2) Fast Read Number of Mode Bits : [%u]\n", sfdp->Modebit122FR);
		printf("(1-2-2) Fast Read Opcode : [0x%02X]\n", sfdp->Op122FR);

		printf("Supports (2-2-2) Fast Read : [%u]\n", sfdp->Sup222FastRead);
		printf("(2-2-2) Fast Read Number of Wait states (dummy clocks) needed before valid output : [%u]\n", sfdp->DummyClock222FR);
		printf("(2-2-2) Fast Read Number of Mode Bits : [%u]\n", sfdp->Modebit222FR);
		printf("(2-2-2) Fast Read Opcode : [0x%02X]\n", sfdp->Op222FR);

		printf("Supports (4-4-4) Fast Read : [%u]\n", sfdp->Sup444FastRead);
		printf("(4-4-4) Fast Read Number of Wait states (dummy clocks) needed before valid output : [%u]\n", sfdp->DummyClock444FR);
		printf("(4-4-4) Fast Read Number of Mode Bits : [%u]\n", sfdp->Modebit444FR);
		printf("(4-4-4) Fast Read Opcode : [0x%02X]\n", sfdp->Op444FR);

		printf("Sector Type 1 Size   : [0x%02X]\n", sfdp->SectorType1Size);
		printf("Sector Type 1 Opcode : [0x%02X]\n", sfdp->SectorType1Op);
		printf("Sector Type 2 Size   : [0x%02X]\n", sfdp->SectorType2Size);
		printf("Sector Type 2 Opcode : [0x%02X]\n", sfdp->SectorType2Op);
		printf("Sector Type 3 Size   : [0x%02X]\n", sfdp->SectorType3Size);
		printf("Sector Type 3 Opcode : [0x%02X]\n", sfdp->SectorType3Op);
		printf("Sector Type 4 Size   : [0x%02X]\n", sfdp->SectorType4Size);
		printf("Sector Type 4 Opcode : [0x%02X]\n", sfdp->SectorType4Op);

		printf("================================\n");
	} else {
		_Rprintf("SFDP Data Error\n");
	}
}

void SflsRegShow(ENX_YN isDetail)
{
	_Cprintf("SFLS Register View\n");
	printf("========================================\n");
	if (isDetail == ENX_YES) {
		_Yprintf(" 0:0x%08X\n", _cm(REG_BASE_SFLS, 0));
		printf("   %-20s: 0x%06X, %u\n", "ID", SFLS_ID, SFLS_ID);
		printf("   %-20s: %u\n", "IF_RST", SFLS_IF_RST);
		printf("   %-20s: %u\n", "ID_VAL", SFLS_ID_VAL);
		_Yprintf(" 1:0x%08X\n", _cm(REG_BASE_SFLS, 1));
		printf("   %-20s: 0x%02X, %u\n", "BUS_CMD_RD", SFLS_BUS_CMD_RD, SFLS_BUS_CMD_RD);
		printf("   %-20s: 0x%02X, %u\n", "BUS_CMD_WR", SFLS_BUS_CMD_WR, SFLS_BUS_CMD_WR);
		printf("   %-20s: 0x%02X, %u\n", "BUS_CMD_WREN", SFLS_BUS_CMD_WREN, SFLS_BUS_CMD_WREN);
		printf("   %-20s: 0x%02X, %u\n", "BUS_CMD_RDREG", SFLS_BUS_CMD_RDREG, SFLS_BUS_CMD_RDREG);
		_Yprintf(" 2:0x%08X\n", _cm(REG_BASE_SFLS, 2));
		printf("   %-20s: %u\n", "BUS_RD_CMD_MODE", SFLS_BUS_RD_CMD_MODE);
		printf("   %-20s: %u\n", "BUS_RD_ADR_MODE", SFLS_BUS_RD_ADR_MODE);
		printf("   %-20s: %u\n", "BUS_RD_DAT_MODE", SFLS_BUS_RD_DAT_MODE);
		printf("   %-20s: %u\n", "BUS_WR_CMD_MODE", SFLS_BUS_WR_CMD_MODE);
		printf("   %-20s: %u\n", "BUS_WR_ADR_MODE", SFLS_BUS_WR_ADR_MODE);
		printf("   %-20s: %u\n", "BUS_WR_DAT_MODE", SFLS_BUS_WR_DAT_MODE);
		printf("   %-20s: %u\n", "BUS_WREN_CMD_MODE", SFLS_BUS_WREN_CMD_MODE);
		printf("   %-20s: %u\n", "BUS_RDREG_CMD_MODE", SFLS_BUS_RDREG_CMD_MODE);
		printf("   %-20s: %u\n", "BUS_RDREG_DAT_MODE", SFLS_BUS_RDREG_DAT_MODE);
		printf("   %-20s: %u\n", "BUS_ADR_EXT", SFLS_BUS_ADR_EXT);
#if (EN675_SINGLE==0)
		printf("   %-20s: %u\n", "BUS_GAP_EN", SFLS_BUS_GAP_EN);
		printf("   %-20s: %u\n", "BUS_GAP", SFLS_BUS_GAP);
#else
		printf("   %-20s: %u\n", "BUS_RDLTC", SFLS_BUS_RDLTC);
#endif
		_Yprintf(" 3:0x%08X\n", _cm(REG_BASE_SFLS, 3));
		printf("   %-20s: 0x%02X, %u\n", "USR_CMD_RDREG", SFLS_USR_CMD_RDREG, SFLS_USR_CMD_RDREG);
		printf("   %-20s: %u\n", "USR_RDREG_CMD_MODE", SFLS_USR_RDREG_CMD_MODE);
		printf("   %-20s: %u\n", "USR_RDREG_DAT_MODE", SFLS_USR_RDREG_DAT_MODE);
#if (EN675_SINGLE==1)
		printf("   %-20s: %u\n", "USR_RDLTC", SFLS_USR_RDLTC);
#endif
		_Yprintf(" 4:0x%08X\n", _cm(REG_BASE_SFLS, 4));
		printf("   %-20s: %u\n", "USR_CMD_MODE", SFLS_USR_CMD_MODE);
		printf("   %-20s: %u\n", "USR_ADR_MODE", SFLS_USR_ADR_MODE);
		printf("   %-20s: %u\n", "USR_DAT_MODE", SFLS_USR_DAT_MODE);
		printf("   %-20s: %u\n", "USR_ADR_EN", SFLS_USR_ADR_EN);
#if (EN675_SINGLE==0)
		printf("   %-20s: %u\n", "USR_GAP_EN", SFLS_USR_GAP_EN);
		printf("   %-20s: %u\n", "USR_GAP", SFLS_USR_GAP);
		printf("   %-20s: %u\n", "USR_RD_EN", SFLS_USR_RD_EN);
		printf("   %-20s: %u\n", "USR_WR_EN", SFLS_USR_WR_EN);
		printf("   %-20s: %u\n", "USR_LEN", SFLS_USR_LEN);
		printf("   %-20s: %u\n", "USR_ADR_EXT", SFLS_USR_ADR_EXT);
		printf("   %-20s: %u\n", "USR_BUSY_EN", SFLS_USR_BUSY_EN);
		printf("   %-20s: %u\n", "USR_RDLTC", SFLS_USR_RDLTC);
#else
		printf("   %-20s: %u\n", "USR_RD_EN", SFLS_USR_RD_EN);
		printf("   %-20s: %u\n", "USR_RD_FULL", SFLS_USR_RD_FULL);
		printf("   %-20s: %u\n", "USR_RD_EMPTY", SFLS_USR_RD_EMPTY);
		printf("   %-20s: %u\n", "USR_WR_EN", SFLS_USR_WR_EN);
		printf("   %-20s: %u\n", "USR_WR_FULL", SFLS_USR_WR_FULL);
		printf("   %-20s: %u\n", "USR_WR_EMPTY", SFLS_USR_WR_EMPTY);
		printf("   %-20s: %u\n", "USR_LEN", SFLS_USR_LEN);
		printf("   %-20s: %u\n", "USR_ADR_EXT", SFLS_USR_ADR_EXT);
		printf("   %-20s: %u\n", "USR_BUSY_EN", SFLS_USR_BUSY_EN);
#endif
		printf("   %-20s: 0x%02X, %u\n", "USR_CMD", SFLS_USR_CMD, SFLS_USR_CMD);
		_Yprintf(" 5:0x%08X\n", _cm(REG_BASE_SFLS, 5));
		printf("   %-20s: 0x%08X, %u\n", "USR_ADR", SFLS_USR_ADR, SFLS_USR_ADR);
		_Yprintf(" 6:0x%08X\n", _cm(REG_BASE_SFLS, 6));
		printf("   %-20s: 0x%08X, %u\n", "USR_RDDAT", SFLS_USR_RDDAT, SFLS_USR_RDDAT);
		_Yprintf(" 7:0x%08X\n", _cm(REG_BASE_SFLS, 7));
		printf("   %-20s: 0x%08X, %u\n", "USR_WRDAT", SFLS_USR_WRDAT, SFLS_USR_WRDAT);
		_Yprintf(" 8:0x%08X\n", _cm(REG_BASE_SFLS, 8));
		printf("   %-20s: %u\n", "IO_RXEDGE", SFLS_IO_RXEDGE);
		printf("   %-20s: %u\n", "IO_TXEDGE", SFLS_IO_TXEDGE);
#if (EN675_SINGLE==0)
		printf("   %-20s: %u\n", "IO_RDLTC", SFLS_IO_RDLTC);
#endif
		printf("   %-20s: %u\n", "IO_CLKDIV", SFLS_IO_CLKDIV);
		printf("   %-20s: %u\n", "IO_CS_GAP", SFLS_IO_CS_GAP);
		printf("   %-20s: %u\n", "USRBUS_REQ", SFLS_USRBUS_REQ);
		printf("   %-20s: %u\n", "BUS_REQ", SFLS_BUS_REQ);
		printf("   %-20s: %u\n", "USR_REQ", SFLS_USR_REQ);
#if (EN675_SINGLE==1)
		_Yprintf(" 9:0x%08X\n", _cm(REG_BASE_SFLS, 9));
		printf("   %-20s: %u\n", "BUS_MODE_VALUE", SFLS_BUS_MODE_VALUE);
		printf("   %-20s: %u\n", "BUS_MODE_EN", SFLS_BUS_MODE_EN);
		printf("   %-20s: %u\n", "BUS_GAP", SFLS_BUS_GAP);
		printf("   %-20s: %u\n", "USR_MODE_VALUE", SFLS_USR_MODE_VALUE);
		printf("   %-20s: %u\n", "USR_MODE_EN", SFLS_USR_MODE_EN);
		printf("   %-20s: %u\n", "USR_GAP", SFLS_USR_GAP);
#endif
	} else {
		printf("SFLS  0:0x%08X  1:0x%08X  2:0x%08X  3:0x%08X  4:0x%08X\n", _cm(REG_BASE_SFLS, 0), _cm(REG_BASE_SFLS, 1), _cm(REG_BASE_SFLS, 2), _cm(REG_BASE_SFLS, 3), _cm(REG_BASE_SFLS, 4));
		printf("SFLS  6:0x%08X  7:0x%08X  8:0x%08X\n", _cm(REG_BASE_SFLS, 5), _cm(REG_BASE_SFLS, 6), _cm(REG_BASE_SFLS, 7), _cm(REG_BASE_SFLS, 8));
	}
	printf("========================================\n");
}
