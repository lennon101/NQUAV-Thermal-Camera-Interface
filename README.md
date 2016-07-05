# NQUAV-Thermal-Camera-Interface
Wireless System for FLIR Tau 2 Thermal Imaging Camera 

NQ UAV purchased two CyberQuad Maxi UAVs which came mounted with a thermal imaging camera produced by FLIR. The CyberQuad Maxi was eventually found to be an unsuitable craft for NQ UAV operations however there was a need to remove the Tau 2 Thermal Imaging Camera and mount it to the preferred DJI S1000 UAV and control the camera wirelessly. 

The camera’s onboard processor and memory was only available using the proprietary Video Power Com (VPC) accessory which plugged into the back of the camera via a 50 pin Hirose connector.  The VPC came with a mini-USB port allowing control of the camera using the FLIR Camera Controller software. However, wireless control of the camera was not possible via these means making the VPC accessory incompatible with the NQ UAV’s requirements. 

I was tasked with the role of researching and developing a prototype for an embedded interface system to allow wireless control of the FLIR Tau 2 Thermal Camera. To be successful, the Thermal Camera had to be remotely operated from a distance and store up to twenty thermal images to its onboard flash memory. The system would increase the capability of NQ UAV allowing the company to offer thermal imaging to future clients. 

To prepare for this project, I first had to familiarise myself with the documentation for the FLIR TAU 2 Camera. This included understanding the protocols sent to the camera to initiate a snapshot command and the content of the frames to do so. To complete the task, hardware needed to be developed along side the software in order to allow wireless control and communications to the camera. 

NQ UAV’s employees had attempted to make use of the Tau2 Wearsaver board (which exposes 20 of the 50 pins from the Hirose connector) and xBees with the intent of creating a pseudo-wireless USB connection while still using the Camera Controller software on the computer. However, it was found that the xBee’s FTDI chips corrupted the information passed to the camera. 

I began developing an Arduino based platform utilising the Wearsaver board and the xBees with an Arduino Uno sending frames via the RS232 serial protocol. This meant that the camera controller software could not be used and the content of the frames had to be explicitly defined. 

After initially struggling with understanding the construction of the frames, NQ UAV enlisted the help of Grant Bajema (Electrical Engineer and Managing Director of Bajtech). NQ UAV and BajTech have an ongoing relationship and Grant was called to provide me with some assistance and direction regarding the Tau 2 Thermal Camera. Grants suggestion was to make use of a software sniffer to capture the hexadecimal data being sent to and from the computer and camera. 

Through this method I was able to reverse engineer the frames that were sent to the camera during set up and the snapshot command.  Arduino scripts for use in an Arduino development board were developed to send and receive hexadecimal fames to and from the Tau2 Thermal Camera. An Arduino joy-stick shield was installed on the Arduino development board and scripts developed to initiate the snapshot command on the camera. Figure 1 shows the final product plugged into the gimbal frame of the DJI S1000. 

