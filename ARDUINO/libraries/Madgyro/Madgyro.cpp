#include "CurieIMU.h"
#include "MadgwickAHRS.h"
#include "Arduino.h"
#include "Madgyro.h"

Madgyro::Madgyro() {

	  // initialize device
	CurieIMU.begin();

	if (calibrateOffsets) {
		// use the code below to calibrate accel/gyro offset values
		/*
		Serial.println("Internal sensor offsets BEFORE calibration...");
		Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS)); Serial.print("\t");
		Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS)); Serial.print("\t");
		Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS)); Serial.print("\t");
		Serial.print(CurieIMU.getGyroOffset(X_AXIS)); Serial.print("\t");
		Serial.print(CurieIMU.getGyroOffset(Y_AXIS)); Serial.print("\t");
		Serial.print(CurieIMU.getGyroOffset(Z_AXIS)); Serial.print("\t");
		Serial.println("");
		*/

		// To manually configure offset compensation values, use the following methods instead of the autoCalibrate...() methods below
		//    CurieIMU.setGyroOffset(X_AXIS, 220);
		//    CurieIMU.setGyroOffset(Y_AXIS, 76);
		//    CurieIMU.setGyroOffset(Z_AXIS, -85);
		//    CurieIMU.setAccelerometerOffset(X_AXIS, -76);
		//    CurieIMU.setAccelerometerOffset(Y_AXIS, -235);
		//    CurieIMU.setAccelerometerOffset(Z_AXIS, 168);

		//IMU device must be resting in a horizontal position for the following calibration procedure to work correctly!

		//Serial.print("Starting Gyroscope calibration...");
		CurieIMU.autoCalibrateGyroOffset();
		//Serial.println(" Done");
		//Serial.print("Starting Acceleration calibration...");
		CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
		CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
		CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
		//Serial.println(" Done");
		/*
		Serial.println("Internal sensor offsets AFTER calibration...");
		Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS)); Serial.print("\t");
		Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS)); Serial.print("\t");
		Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS)); Serial.print("\t");
		Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS)); Serial.print("\t");
		Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS)); Serial.print("\t");
		Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS)); Serial.print("\t");
		Serial.println("");
		*/
	}
}

float Madgyro::readYaw() {
  // read raw accel/gyro measurements from device
  CurieIMU.readMotionSensor(ax, ay, az, gx, gy, gz); 

  // use function from MagdwickAHRS.h to return quaternions
  filter.updateIMU(gx / factor, gy / factor, gz / factor, ax, ay, az);

  // functions to find yaw roll and pitch from quaternions
  theyaw = filter.getYaw();

  return theyaw;
}

void Madgyro::calibrate() { //Force calibration
	// use the code below to calibrate accel/gyro offset values
	/*
	Serial.println("Internal sensor offsets BEFORE calibration...");
	Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS)); Serial.print("\t");
	Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS)); Serial.print("\t");
	Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS)); Serial.print("\t");
	Serial.print(CurieIMU.getGyroOffset(X_AXIS)); Serial.print("\t");
	Serial.print(CurieIMU.getGyroOffset(Y_AXIS)); Serial.print("\t");
	Serial.print(CurieIMU.getGyroOffset(Z_AXIS)); Serial.print("\t");
	Serial.println("");
	*/

	// To manually configure offset compensation values, use the following methods instead of the autoCalibrate...() methods below
	//    CurieIMU.setGyroOffset(X_AXIS, 220);
	//    CurieIMU.setGyroOffset(Y_AXIS, 76);
	//    CurieIMU.setGyroOffset(Z_AXIS, -85);
	//    CurieIMU.setAccelerometerOffset(X_AXIS, -76);
	//    CurieIMU.setAccelerometerOffset(Y_AXIS, -235);
	//    CurieIMU.setAccelerometerOffset(Z_AXIS, 168);

	//IMU device must be resting in a horizontal position for the following calibration procedure to work correctly!

	//Serial.print("Starting Gyroscope calibration...");
	CurieIMU.autoCalibrateGyroOffset();
	//Serial.println(" Done");
	//Serial.print("Starting Acceleration calibration...");
	CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
	CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
	CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
	//Serial.println(" Done");
	/*
	Serial.println("Internal sensor offsets AFTER calibration...");
	Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS)); Serial.print("\t");
	Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS)); Serial.print("\t");
	Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS)); Serial.print("\t");
	Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS)); Serial.print("\t");
	Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS)); Serial.print("\t");
	Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS)); Serial.print("\t");
	Serial.println("");
	*/
}