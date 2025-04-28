/*
 * MCP23017.h
 *
 *  Created on: Mar 25, 2025
 *      Author: snb70
 */

#ifndef SRC_GPIO_I2C_MCP23017_H_
#define SRC_GPIO_I2C_MCP23017_H_

#ifdef __cplusplus
extern "C" {
#endif

#if 1
#include "stm32f4xx_hal.h"
#if 0
IODIR:  I/O方向レジスタ(ADDR 0x00)
 1 =ピンを入力として設定する
 0 =ピンを出力として設定する
IPOL:  入力極性ポートレジスタ(ADDR 0x01)
 1 =入力ピンの論理状態と反対の論理状態がGPIOレジスタビットに反映される
 0 =入力ピンの論理状態と同じ論理状態がGPIOレジスタビットに反映される
GPINTEN:  状態変化割り込みピン(ADDR 0x02)
 1 = 状態変化割り込みイベントに対してGPIO入力ピンを有効にする
 0 = 状態変化割り込みイベントに対してGPIO入力ピンを無効にする
DEFVAL:  既定値レジスタ(ADDR 0x03)

INTCON:  状態変化割り込み制御レジスタ(ADDR 0x04)

IOCON:  I/Oエ クスパンダ コンフィグレーション レジスタ(ADDR 0x05)

GPPU:  GPIOプ ルアップ抵抗レジスタ(ADDR 0x06)
 1 = プルアップ抵抗を有効にする
 0 = プルアップ抵抗を無効にする
INTF:  割り込みフラグレジスタ(ADDR 0x07)
 1 = ピンが割り込みを発生した
 0 = 保留中の割り込みはない
INTCAP:  割り込み時にキャプチャしたポート値を示すレジスタ(ADDR 0x08)
 1 = 論理High
 0 = 論理Low
GPIO:  汎用I/Oポートレジスタ(ADDR 0x09)
 1 = 論理High
 0 = 論理Low
OLAT:  出力ラッチレジスタ0 (ADDR 0x0A)
 1 = 論理High
 0 = 論理Low
#endif

 //MCP23017 No1 PORT A
 #define M_SW0 0x201280
 #define M_SW1 0x201240
 #define M_SW2 0x201220
 #define M_SW3 0x201210
 #define M_SW4 0x201208
 #define M_SW5 0x201204
 #define M_SW6 0x201202
 #define M_SW7 0x201201

 //MCP23017 No1 PORT B
 #define M_LED0 0x201501
 //#define M_LED0 0x201501 | 0x800000//(1)
 #define M_LED1 0x201502
 #define M_LED2 0x201504
 #define M_LED3 0x201508
 #define M_LED4 0x201510
 #define M_LED5 0x201520
 #define M_LED6 0x201540
 #define M_LED7 0x201580
 //#define M_LED0      0x201501
 //#define M_LED0_INV  (M_LED0 | 0x800000)  // 0x800000 のビットを立てる

#if 1
// Registers
// Bank=0
#define MCP23017_IODIRA		0x00
#define MCP23017_IODIRB		0x01
#define MCP23017_IPOLA		0x02
#define MCP23017_IPOLB		0x03
#define MCP23017_GPINTENA	0x04
#define MCP23017_GPINTENB	0x05
#define MCP23017_DEFVALA	0x06
#define MCP23017_DEFVALB	0x07
#define MCP23017_INTCONA	0x08
#define MCP23017_INTCONB	0x09

#define	MCP23017_IOCONA			0x0A
#define	MCP23017_IOCONB			0x0B

#define MCP23017_GPPUA		0x0C
#define MCP23017_GPPUB		0x0D
#define MCP23017_INTFA		0x0E
#define MCP23017_INTFB		0x0F
#define MCP23017_INTCAPA	0x10
#define MCP23017_INTCAPB	0x11
#define MCP23017_GPIOA		0x12
#define MCP23017_GPIOB		0x13
#define MCP23017_OLATA		0x14
#define MCP23017_OLATB		0x15
// Ports
#define MCP23017_PORTA			0x00
#define MCP23017_PORTB			0x01

// Address (A0-A2)
#define MCP23017_ADDRESS_20		0x20
#define MCP23017_ADDRESS_21		0x21
#define MCP23017_ADDRESS_22		0x22
#define MCP23017_ADDRESS_23		0x23
#define MCP23017_ADDRESS_24		0x24
#define MCP23017_ADDRESS_25		0x25
#define MCP23017_ADDRESS_26		0x26
#define MCP23017_ADDRESS_27		0x27

// I/O Direction
// Default state: MCP23017_IODIR_ALL_INPUT
#define MCP23017_IODIR_ALL_OUTPUT	0x00
#define MCP23017_IODIR_ALL_INPUT	0xFF
#define MCP23017_IODIR_IO0_INPUT	0x01
#define MCP23017_IODIR_IO1_INPUT	0x02
#define MCP23017_IODIR_IO2_INPUT	0x04
#define MCP23017_IODIR_IO3_INPUT	0x08
#define MCP23017_IODIR_IO4_INPUT	0x10
#define MCP23017_IODIR_IO5_INPUT	0x20
#define MCP23017_IODIR_IO6_INPUT	0x40
#define MCP23017_IODIR_IO7_INPUT	0x80

// Input Polarity
// Default state: MCP23017_IPOL_ALL_NORMAL
#define MCP23017_IPOL_ALL_NORMAL	0x00
#define MCP23017_IPOL_ALL_INVERTED	0xFF
#define MCP23017_IPOL_IO0_INVERTED	0x01
#define MCP23017_IPOL_IO1_INVERTED	0x02
#define MCP23017_IPOL_IO2_INVERTED	0x04
#define MCP23017_IPOL_IO3_INVERTED	0x08
#define MCP23017_IPOL_IO4_INVERTED	0x10
#define MCP23017_IPOL_IO5_INVERTED	0x20
#define MCP23017_IPOL_IO6_INVERTED	0x40
#define MCP23017_IPOL_IO7_INVERTED	0x80

// Pull-Up Resistor
// Default state: MCP23017_GPPU_ALL_DISABLED
#define MCP23017_GPPU_ALL_DISABLED	0x00
#define MCP23017_GPPU_ALL_ENABLED	0xFF
#define MCP23017_GPPU_IO0_ENABLED	0x01
#define MCP23017_GPPU_IO1_ENABLED	0x02
#define MCP23017_GPPU_IO2_ENABLED	0x04
#define MCP23017_GPPU_IO3_ENABLED	0x08
#define MCP23017_GPPU_IO4_ENABLED	0x10
#define MCP23017_GPPU_IO5_ENABLED	0x20
#define MCP23017_GPPU_IO6_ENABLED	0x40
#define MCP23017_GPPU_IO7_ENABLED	0x80
#endif

void GPIO23017_write_reg(uint8_t addr, uint8_t data);
//void GPIO23017_read_reg(uint8_t addr, uint8_t data);

void GPIO23017_chkComm(void);
void GPIO23017_ini(void);
void set_pin(uint32_t n);
void rst_pin(uint32_t n);
uint8_t get_pin(uint32_t n);

//buf版追加2025/04/27
//I2C通信エラー時MCP23017の出力が全てONになるので配列化の試作前?。
typedef struct {
    uint8_t i2c_addr;          	// I2Cアドレス
    uint8_t output_data[2];  	// 出力用の影データ（GPIOA, GPIOB）
    uint8_t input_data[2];  	// 入力用の影データ（GPIOA, GPIOB）
    uint8_t direction[2];       // 入力(1)または出力(0)設定（GPIOA, GPIOB）
} MCP23017_Device;
//MCP23017一個の時。2個なら4と増やす。
//PORT A PORT B
#define MCP23017_DEVICE_MAX 2
#define MCP23017_START_ADD 0x20

void MCP23read_allport_to_buf(void);//全ての入出力をバッファにコピー(初期状態を記憶)
void MCP23set_buf(void);			//アドレス入出力指定
void MCP23set_buf_allclear(void);	//取り合えずportデータークリア

void MCP23set_pin_buf(uint32_t n);//bufのbit on
void MCP23rst_pin_buf(uint32_t n);//bufのbit off
void MCP23write_port(uint8_t addr);//指定アドレスの書き込み(入力出力を判断してbufの内容をポートに反映)
void MCP23write_all_port(void);//入力出力を判断して全てのbufの内容をポートに反映

void MCP23read_input_once(void);//ポーリング時入力のみbufに取り込む
uint8_t MCP23get_pin_buf(uint32_t n);//取り込んだbufの指定bitがonかoffか調べる
void MCP23_buf_test(void);


#if 0
typedef struct {
	I2C_HandleTypeDef*	hi2c;
	uint16_t		addr;
	uint8_t			gpio[2];
} MCP23017_HandleTypeDef;

void    		mcp23017_init(MCP23017_HandleTypeDef *hdev, I2C_HandleTypeDef *hi2c, uint16_t addr);
HAL_StatusTypeDef	mcp23017_read(MCP23017_HandleTypeDef *hdev, uint16_t reg, uint8_t *data);
HAL_StatusTypeDef	mcp23017_write(MCP23017_HandleTypeDef *hdev, uint16_t reg, uint8_t *data);
HAL_StatusTypeDef	mcp23017_iodir(MCP23017_HandleTypeDef *hdev, uint8_t port, uint8_t iodir);
HAL_StatusTypeDef	mcp23017_ipol(MCP23017_HandleTypeDef *hdev, uint8_t port, uint8_t ipol);
HAL_StatusTypeDef	mcp23017_ggpu(MCP23017_HandleTypeDef *hdev, uint8_t port, uint8_t pu);
HAL_StatusTypeDef	mcp23017_read_gpio(MCP23017_HandleTypeDef *hdev, uint8_t port);
HAL_StatusTypeDef	mcp23017_write_gpio(MCP23017_HandleTypeDef *hdev, uint8_t port);
#endif
#endif

#ifdef __cplusplus
}
#endif
#endif /* SRC_GPIO_I2C_MCP23017_H_ */
