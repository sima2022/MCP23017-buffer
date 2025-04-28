/*
 * MCP23017.c
 *
 *  Created on: Mar 25, 2025
 *      Author: snb70
 I²C アドレス: MCP23017 のアドレスは 0x20 ～ 0x27（A0～A2の設定次第）。

レジスタ設定

IODIRA (0x00): GPIOA の方向設定 (0=出力, 1=入力)
GPIOA (0x12): GPIOA のデータ出力
IODIRB (0x01): GPIOB の方向設定
GPIOB (0x13): GPIOB のデータ出力

 */
#include "MCP23017.h"
#include "GPIO_I2C.H"
#include <string.h>
#if 0
// Registers
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
//	IOCON			0x0A
//	IOCON			0x0B
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


//MCP23017 No1 PORT A
#define M_SW0 0xf00001
#define M_SW1 0x000002
#define M_SW2 0x000004
#define M_SW3 0x000008
#define M_SW4 0x000010
#define M_SW5 0x000020
#define M_SW6 0x000040
#define M_SW7 0x000080

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
#endif

void GPIO23017_write_reg(uint8_t addr, uint8_t data){
    I2C_Start();
    I2C_WriteByte(addr);
    I2C_WriteByte(data);
    I2C_Stop();
}
//void GPIO23017_read_reg(uint8_t addr, uint8_t data){
//
//}

void GPIO23017_chkComm(void){
	uint8_t ans;
	ans=I2C_AddressScanning(MCP23017_ADDRESS_20);//0x20配線済み
	ans=I2C_AddressScanning(MCP23017_ADDRESS_21);//0x21配線なし
}
void GPIO23017_ini(void){
#if 0
	  I2C_Start();
	  I2C_WriteByte((MCP23017_ADDRESS_20 << 1) | 0x00);
	  I2C_WriteByte(MCP23017_IODIRA);
	  I2C_WriteByte(MCP23017_IODIR_ALL_INPUT);
	  I2C_Stop();
	  I2C_Start();
	  I2C_WriteByte((MCP23017_ADDRESS_20 << 1) | 0x00);  // MCP23017のI2Cアドレス（書き込みモード）
	  I2C_WriteByte(MCP23017_IODIRB);  // IODIRBレジスタ（GPIOBの方向設定）
	  I2C_WriteByte(MCP23017_IODIR_ALL_OUTPUT);  // すべて出力（0=出力, 1=入力）
	  I2C_Stop();

	  I2C_Start();
	  I2C_WriteByte((MCP23017_ADDRESS_20 << 1) | 0x00);
	  I2C_WriteByte(0x0C);  // GPPUAレジスタ（GPIOAのプルアップ設定）
	  I2C_WriteByte(0xff);  // プルアップを有効にする
	  I2C_Stop();

	  set_pin(M_LED0);




	I2C_Start();
	GPIO23017_write_reg(0x0A, 0);//IOCON
	//I2C_Stop();
	//I2C_Start();
	GPIO23017_write_reg(0x0B, 0);//IOCON
	//I2C_Stop();
	//I2C_Start();
	// IODIRAレジスタを設定: Aポートをすべて出力に
	GPIO23017_write_reg(MCP23017_IODIRA, MCP23017_IODIR_ALL_OUTPUT);
	//I2C_Stop();
	//I2C_Start();
	GPIO23017_write_reg(MCP23017_IODIRB,MCP23017_IODIR_ALL_INPUT);
	//I2C_Stop();

	//GPIO23017_write_reg(MCP23017_IPOLA,MCP23017_IPOL_ALL_NORMAL);//入力極性ポートレジスタ
	//GPIO23017_write_reg(MCP23017_IPOLB,MCP23017_IPOL_ALL_NORMAL);
	GPIO23017_write_reg(MCP23017_GPINTENA,MCP23017_GPPU_ALL_ENABLED);//状態変化割り込みピン
	GPIO23017_write_reg(MCP23017_GPINTENB,MCP23017_GPPU_ALL_ENABLED);
	//GPIO23017_write_reg(MCP23017_DEFVALA,);// DEFVAL:  既定値レジスタ
	//GPIO23017_write_reg(MCP23017_DEFVALB,);
	//GPIO23017_write_reg(MCP23017_INTCONA,);// INTCON:  状態変化割り込み制御レジスタ
	//GPIO23017_write_reg(MCP23017_INTCONB,);
	//I2C_Start();
	GPIO23017_write_reg(MCP23017_GPPUA,0);//GPPU:  GPIOプルアップ抵抗レジスタ 0=プルアップ無
	//I2C_Stop();
	//I2C_Start();
	GPIO23017_write_reg(MCP23017_GPPUB,0xff);//1=プルアップあり
	I2C_Stop();
#endif
	//GPIO23017_write_reg(MCP23017_INTFA,MCP23017_GPPU_ALL_DISABLED);//INTF:  割り込みフラグレジスタ
	//GPIO23017_write_reg(MCP23017_INTFB,MCP23017_GPPU_ALL_DISABLED);
	//GPIO23017_write_reg(MCP23017_INTCAPA,MCP23017_GPPU_ALL_DISABLED);//INTCAP:  割り込み時にキャプチャしたポート値を示すレジスタ
	//GPIO23017_write_reg(MCP23017_INTCAPB,MCP23017_GPPU_ALL_DISABLED);
	//GPIO23017_write_reg(MCP23017_GPIOA,);//GPIO:  汎用I/Oポートレジスタ 1 = 論理High
	//GPIO23017_write_reg(MCP23017_GPIOB,);
	//GPIO23017_write_reg(MCP23017_OLATA,);//OLAT:  出力ラッチレジスタ 1 = 論理High
	//GPIO23017_write_reg(MCP23017_OLATB,);

#if 0
    if (expIO_Read(GPB,GPB0) == 0) {   // SWは押されたか？
              expIO_Write(GPA,GPA7,HIGH) ;  // SW=ON ならLED点灯
         } else expIO_Write(GPA,GPA7,LOW) ; // LED消灯

#endif
}
void set_pin(uint32_t n){
//volatile は不要?
    uint8_t a, p, b,ack;
    uint8_t port_value;

    a = (n >> 16) & 0xFF;  // 上位8ビット（I2Cアドレス）
    p = (n >> 8) & 0xFF;   // 中間8ビット（レジスタアドレス）
    b = n & 0xFF;          // 下位8ビット（ビット番号）

    // 1. 現在のポート値を読み取る
    I2C_Start();
    I2C_WriteByte((a << 1) | 0x00);  // MCP23017のアドレス（Writeモード）
    I2C_WriteByte(p);                // 対象のポートレジスタ
    I2C_Stop();

    I2C_Start();
    ack=I2C_WriteByte((a << 1) | 0x01);  // MCP23017のアドレス（Readモード）
    if(ack==0){
    	port_value = I2C_ReadByte(1);     // 現在のポート値を取得
    }else{}
    I2C_Stop();

    // 2. 指定したビットをセット（ONにする）
    port_value |= b;//(1 << b);

    // 3. 新しいポート値を書き込む
    I2C_Start();
    I2C_WriteByte((a << 1) | 0x00);  // MCP23017のアドレス（Writeモード）
    I2C_WriteByte(p);                // 対象のポートレジスタ
    I2C_WriteByte(port_value);       // 更新した値を書き込み
    I2C_Stop();
}
void rst_pin(uint32_t n){
     uint8_t a, p, b,ack;
     uint8_t port_value;
//     uint8_t invert = (n >> 31) & 0x01;  // 31bit目を取得（負論理フラグ）//(1)

     a = (n >> 16) & 0xFF;
     p = (n >> 8) & 0xFF;
     b = n & 0xFF;

     I2C_Start();
     I2C_WriteByte((a << 1) | 0x00);
     I2C_WriteByte(p);
     I2C_Stop();

     I2C_Start();
     ack=I2C_WriteByte((a << 1) | 0x01);
     if(ack==0){
    	 port_value = I2C_ReadByte(1);
     }else{}
     I2C_Stop();

     // 指定ビットをクリア（OFF）
     port_value &= ~b;
     // 2. 指定したビットをセットまたはクリア
//     port_value ^= (-invert ^ port_value) & (1 << b);//(1)

     I2C_Start();
     I2C_WriteByte((a << 1) | 0x00);
     I2C_WriteByte(p);
     I2C_WriteByte(port_value);
     I2C_Stop();
}
uint8_t get_pin(uint32_t n){
    uint8_t a, p, b,ack;
    uint8_t port_value;
//     uint8_t invert = (n >> 31) & 0x01;  // 31bit目を取得（負論理フラグ）//(1)

    a = (n >> 16) & 0xFF;
    p = (n >> 8) & 0xFF;
    b = n & 0xFF;

    I2C_Start();
    I2C_WriteByte((a << 1) | 0x00);
    I2C_WriteByte(p);
    I2C_Stop();

    I2C_Start();
    ack=I2C_WriteByte((a << 1) | 0x01);
    if(ack==0){
   	 port_value = I2C_ReadByte(1);
    }else{}
    I2C_Stop();

    return (port_value & b) ? 1 : 0; // bのビットがONなら1、OFFなら0
}
//buf版追加準備だけ(2025/04/27)
MCP23017_Device MCP23_buf[MCP23017_DEVICE_MAX];
//全ての入出力をバッファにコピー
void MCP23read_allport_to_buf(void){
	uint8_t add = MCP23017_START_ADD;
    uint8_t p1,p2,ack,port_value;
    // デバイス探索
    for (uint8_t dev_idx = 0; dev_idx < MCP23017_DEVICE_MAX; dev_idx++) {
        if(MCP23_buf[dev_idx].direction[0]==1){
        	p1 = MCP23017_GPIOA;
        }else{
        	p1= MCP23017_OLATA;
        }
        if(MCP23_buf[dev_idx].direction[1]==1){
        	p2 = MCP23017_GPIOB;
        }else{
        	p2= MCP23017_OLATB;
        }
        //portA
    	I2C_Start();
        I2C_WriteByte((add << 1) | 0x00);
        I2C_WriteByte(p1);
        I2C_Stop();

        I2C_Start();
        ack=I2C_WriteByte((add << 1) | 0x01);
        if(ack==0){
       	 port_value = I2C_ReadByte(1);
        }else{/**error*/}
        I2C_Stop();
        if(MCP23_buf[dev_idx].direction[0]==1){
        	MCP23_buf[dev_idx].input_data[0] = port_value;
        }else{
        	MCP23_buf[dev_idx].output_data[0] = port_value;
        }
        //portB
    	I2C_Start();
        I2C_WriteByte((add << 1) | 0x00);
        I2C_WriteByte(p2);
        I2C_Stop();

        I2C_Start();
        ack=I2C_WriteByte((add << 1) | 0x01);
        if(ack==0){
       	 port_value = I2C_ReadByte(1);
        }else{/**error*/}
        I2C_Stop();
        if(MCP23_buf[dev_idx].direction[1]==1){
        	MCP23_buf[dev_idx].input_data[1] = port_value;
        }else{
        	MCP23_buf[dev_idx].output_data[1] = port_value;
        }
    }
}
//MCP23017のアドレス設定
//A,Bportの方向設定(入力,出力)
void MCP23set_buf(void){
//portAが入力(1)
//portBが出力の時(0)
	MCP23_buf[0].i2c_addr=0x20;
	MCP23_buf[0].direction[0]=1;//入力(1)
	MCP23_buf[0].direction[1]=0;//出力(0)
	MCP23read_allport_to_buf();
}
void MCP23set_buf_allclear(void){
	//memset(MCP23_buf, 0x0, sizeof(MCP23_buf));  // 全要素を初期化
	for (uint8_t dev_idx = 0; dev_idx < MCP23017_DEVICE_MAX; dev_idx++) {
	    MCP23_buf[dev_idx].output_data[0] = 0x00;  // Port A の出力クリア
	    MCP23_buf[dev_idx].output_data[1] = 0x00;  // Port B の出力クリア
	}
}
//配列でbitの操作だけ。
void MCP23set_pin_buf(uint32_t n){
    uint8_t addr = (n >> 16) & 0xFF;
    uint8_t reg  = (n >> 8)  & 0xFF;
    uint8_t bit  = n & 0xFF;
    // デバイス探索
    for (uint8_t dev_idx = 0; dev_idx < MCP23017_DEVICE_MAX; dev_idx++) {
        if (MCP23_buf[dev_idx].i2c_addr == addr) {
           uint8_t port = (reg == 0x14) ? 0 : (reg == 0x15) ? 1 : 255;  // 0x14はOLATA, 0x15はOLATB
           if (MCP23_buf[dev_idx].direction[port] == 0) {  // 出力設定されているか確認
            	MCP23_buf[dev_idx].output_data[port] |= bit;
            	break;
            }
        }
    }
}
void MCP23rst_pin_buf(uint32_t n){
    uint8_t addr = (n >> 16) & 0xFF;
    uint8_t reg  = (n >> 8)  & 0xFF;
    uint8_t bit  = n & 0xFF;

    for (uint8_t dev_idx = 0; dev_idx < MCP23017_DEVICE_MAX; dev_idx++) {
        if (MCP23_buf[dev_idx].i2c_addr == addr) {
           uint8_t port = (reg == 0x14) ? 0 : (reg == 0x15) ? 1 : 255;  // 0x14はOLATA, 0x15はOLATB
           if (MCP23_buf[dev_idx].direction[port] == 0) {  // 出力設定されているか確認
            	MCP23_buf[dev_idx].output_data[port] &= ~bit;
            	break;
            }
        }
    }
}
//bufの一括書き込み
//まだ出来ていない。
void MCP23write_port(uint8_t addr){
    for (uint8_t dev_idx = 0; dev_idx < MCP23017_DEVICE_MAX; dev_idx++) {
        if (MCP23_buf[dev_idx].i2c_addr == addr) {
            for (uint8_t port = 0; port < 2; port++) {  // Port A / Port B
                uint8_t reg = (port == 0) ? 0x14 : 0x15;  // OLATA / OLATB

                I2C_Start();
                I2C_WriteByte((addr << 1) | 0x00);  // MCP23017アドレス
                I2C_WriteByte(reg);                 // 対象のレジスタ
                I2C_WriteByte(MCP23_buf[dev_idx].output_data[port]);  // 構造体のデータを送信
                I2C_Stop();
            }
            break;  // 対象デバイスを処理したらループを抜ける
        }
    }
}
void MCP23write_all_port(void){
	//for (uint8_t addr = 0x20; addr <= 0x22; addr++) {
	for (uint8_t addr = 0x20; addr <= 0x20+(MCP23017_DEVICE_MAX/2); addr++) {
		MCP23write_port(addr);
	}
}
uint8_t MCP23get_pin_buf(uint32_t n){
    uint8_t addr = (n >> 16) & 0xFF;
    uint8_t reg  = (n >> 8)  & 0xFF;
    uint8_t bit  = n & 0xFF;

    // デバイス探索
    for (uint8_t dev_idx = 0; dev_idx < MCP23017_DEVICE_MAX; dev_idx++) {
        if (MCP23_buf[dev_idx].i2c_addr == addr) {
            uint8_t port = (reg == 0x12) ? 0 : (reg == 0x13) ? 1 : 255;

            if (port == 255) {
                return 0xFF;
            }

            if (MCP23_buf[dev_idx].direction[port] == 1) {
                return (MCP23_buf[dev_idx].input_data[port] & bit) ? 0x01 : 0x00;
            }
        }
    }
    return 0xfe;  // 見つからなかった場合0xfe扱い
}
void MCP23read_input_once(void){
    uint8_t add = MCP23017_START_ADD;
    uint8_t p, ack, port_value;

    // デバイス探索
    for (uint8_t dev_idx = 0; dev_idx < MCP23017_DEVICE_MAX; dev_idx++) {
        for (uint8_t port = 0; port < 2; port++) {  // Port A (0) / Port B (1)
            if (MCP23_buf[dev_idx].direction[port] == 1) {  // 入力モードのみ処理
                p = (port == 0) ? MCP23017_GPIOA : MCP23017_GPIOB;

                I2C_Start();
                I2C_WriteByte((add << 1) | 0x00);  // MCP23017のアドレス (書き込みモード)
                I2C_WriteByte(p);  // GPIOAまたはGPIOBのレジスタ
                I2C_Stop();

                I2C_Start();
                ack = I2C_WriteByte((add << 1) | 0x01);  // MCP23017のアドレス (読取モード)
                if (ack == 0) {
                    port_value = I2C_ReadByte(1);
                    MCP23_buf[dev_idx].input_data[port] = port_value;  // バッファに保存
                }
                I2C_Stop();
            }
        }
    }
}
void MCP23_buf_test(void){
    static uint32_t prev_time = 0;
    static uint8_t state = 0;
    uint32_t now;
    MCP23set_buf();
	while(1){
		if(!MCP23get_pin_buf(M_SW7)){
			MCP23set_pin_buf(M_LED7);
		}else{
			MCP23rst_pin_buf(M_LED7);
		}

		now = HAL_GetTick();  // 現在の時間を取得

	    if (state == 0 && (now - prev_time >= 50)) {
	        MCP23set_pin_buf(M_LED1);
	        MCP23write_all_port();
	        prev_time = now;  // 時間更新
	        state = 1;  // 次のステートへ移行
	    }

	    if (state == 1 && (now - prev_time >= 50)) {
	        MCP23rst_pin_buf(M_LED1);
	        MCP23write_all_port();
	        prev_time = now;  // 時間更新
	        state = 0;  // 次のステートへ移行
	    }
		MCP23read_input_once();

#if 0
		MCP23set_pin_buf(M_LED1);
		MCP23write_all_port();
		HAL_Delay(50);
		MCP23rst_pin_buf(M_LED1);
		MCP23write_all_port();
		HAL_Delay(50);
		MCP23read_input_once();
#endif
	}
}

