#include "mpu6050.h"
#include "math.h"

int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;
int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;

float Ax, Ay, Az, Gx, Gy, Gz;
float roll_a, pitch_a;
float roll_g, pitch_g, yaw_g;
float roll, pitch, yaw;

// 新增：陀螺仪零偏值
static float gyro_x_offset = 0;
static float gyro_y_offset = 0;
static float gyro_z_offset = 0;

// 陀螺仪量程±2000°/s 标准灵敏度系数
#define GYRO_SENS 16.384f
// 加速度量程±16g 标准灵敏度系数
#define ACCEL_SENS 2048.0f
// 互补滤波系数
#define COMPL_ALPHA 0.98f
// 积分时间(单位：秒)，请确保Read_Result调用间隔严格等于此值
#define DT 0.005f

void MPU6050_Init(void)
{
	uint8_t check;
	uint8_t Data;

	HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 1000);

	if (check == 0x68)
	{
		Data = 0x01;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, 1000);
		Data = 0x00;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, PWR_MGMT_2_REG, 1, &Data, 1, 1000);
		Data = 0x06;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, CONFIG, 1, &Data, 1, 1000);
		Data = 0x09;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);
		Data = 0x18;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000);
		Data = 0x18;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);

		// 初始化后自动校准零偏，校准时模块必须静止平放
		MPU6050_Calibrate();
	}
}

// 新增：陀螺仪零偏校准函数
void MPU6050_Calibrate(void)
{
	uint8_t Rec_Data[6];
	int32_t sum_x = 0, sum_y = 0, sum_z = 0;
	const uint16_t cali_cnt = 500; // 采样500次取平均

	for(uint16_t i = 0; i < cali_cnt; i++)
	{
		HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);
		sum_x += (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
		sum_y += (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
		sum_z += (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
		HAL_Delay(2);
	}

	gyro_x_offset = (float)sum_x / cali_cnt;
	gyro_y_offset = (float)sum_y / cali_cnt;
	gyro_z_offset = (float)sum_z / cali_cnt;

	// 校准完成后欧拉角归零
	roll = 0;
	pitch = 0;
	yaw = 0;
}

void MPU6050_Read_Accel(void)
{
	uint8_t Rec_Data[6];
	HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
	Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
	Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

	Ax = Accel_X_RAW / ACCEL_SENS;
	Ay = Accel_Y_RAW / ACCEL_SENS;
	Az = Accel_Z_RAW / ACCEL_SENS - 0.5f; // 保留你的硬件修正
}

void MPU6050_Read_Gyro(void)
{
	uint8_t Rec_Data[6];
	HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

	// 扣除零偏
	Gx = (Gyro_X_RAW - gyro_x_offset) / GYRO_SENS;
	Gy = (Gyro_Y_RAW - gyro_y_offset) / GYRO_SENS;
	Gz = (Gyro_Z_RAW - gyro_z_offset) / GYRO_SENS;
}

void MPU6050_Read_Result(void)
{
	uint8_t Rec_Data_A[6];
	uint8_t Rec_Data_G[6];

	// 读取加速度
	HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data_A, 6, 1000);
	Accel_X_RAW = (int16_t)(Rec_Data_A[0] << 8 | Rec_Data_A[1]);
	Accel_Y_RAW = (int16_t)(Rec_Data_A[2] << 8 | Rec_Data_A[3]);
	Accel_Z_RAW = (int16_t)(Rec_Data_A[4] << 8 | Rec_Data_A[5]);

	Ax = Accel_X_RAW / ACCEL_SENS;
	Ay = Accel_Y_RAW / ACCEL_SENS;
	Az = Accel_Z_RAW / ACCEL_SENS - 0.5f;

	// 读取陀螺仪并扣除零偏
	HAL_I2C_Mem_Read(&hi2c2, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data_G, 6, 1000);
	Gyro_X_RAW = (int16_t)(Rec_Data_G[0] << 8 | Rec_Data_G[1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data_G[2] << 8 | Rec_Data_G[3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data_G[4] << 8 | Rec_Data_G[5]);

	Gx = (Gyro_X_RAW - gyro_x_offset) / GYRO_SENS;
	Gy = (Gyro_Y_RAW - gyro_y_offset) / GYRO_SENS;
	Gz = (Gyro_Z_RAW - gyro_z_offset) / GYRO_SENS;

	// 加速度解算欧拉角
	roll_a = atan2(Ay, Az) / 3.1415926f * 180.0f;
	pitch_a = -atan2(Ax, Az) / 3.1415926f * 180.0f;

	// 陀螺仪积分
	roll_g = roll + Gx * DT;
	pitch_g = pitch + Gy * DT;
	yaw_g = yaw + Gz * DT;

	// 修正后的互补滤波公式
	roll = COMPL_ALPHA * roll_g + (1 - COMPL_ALPHA) * roll_a;
	pitch = COMPL_ALPHA * pitch_g + (1 - COMPL_ALPHA) * pitch_a;
	yaw = yaw_g; // yaw无加速度修正，纯积分
}
