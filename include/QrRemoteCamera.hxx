#pragma once

#include "QrCore.hxx"
#include "QrCamera.hxx"
#include <iostream>

#if defined(_MSC_VER)
//#include <WinSock2.h>
#elif defined(__GNUC__)
#include <opencv2/opencv.hpp>
#endif

namespace QrSDK
{
#pragma pack(push, 1)
    typedef struct FramePacketQVGA
    {
        uint8_t     STX;            // 1    : STX  

        uint32_t    totalLength;    // 4    : Total Length
        uint8_t     txSeqNum;       // 1    : Tx Sequence Number
        uint32_t    length;         // 4    : Length
        uint16_t    command;        // 2    : Command
        uint8_t     frameRate;          // 1    : Frame Rate
        uint16_t    resX;                // 2    : Resolution X size
        uint16_t    resY;        // 2    : Resolution Y size
        uint16_t    vcml;        // 2    : VCM
        float       tempSensor;   // 4    : Temp Sensor
        uint16_t    tempMCU;
        uint16_t    tempBoard;
        uint8_t     fov;
        uint8_t     fNum;
        uint8_t     typeOfCode;
        uint8_t     emissivity;
        uint8_t     extraDataPre;
        uint16_t    refTemp1st;
        uint16_t    refTemp2nd;
        uint16_t    refTemp3rd;
        uint16_t    extraData1;
        uint16_t    extraData2;
        uint16_t    extraData3;
        float       tempNTC;
        uint8_t     calibAvgSeq;
        uint8_t     maxAddr[6];
        uint8_t     algoMode;
        uint8_t     gaussianFilter;
        uint8_t     gaussianWeight;
        uint16_t    calibPart[320 * 10];
        uint16_t    videoFrame[320 * 240];

        uint8_t ETX;

    } tFramePacketQVGA;
#pragma pack(pop)
    /// @brief Remote camera implementation for TCP/IP streaming.
    /// @details QrRemoteCamera extends QrCamera to provide:
    ///   - Establishing and closing a network connection to a remote camera via Connect(addr, port) and Disconnect()
    ///   - Receiving video packets over a socket and reconstructing frames in Read(qrFrame)
    class DLL_EXPORTS QrRemoteCamera : public QrCamera
    {
    private:
#if defined(_MSC_VER)
        SOCKET videoSocket = INVALID_SOCKET;
#elif defined(__GNUC__)
        unsigned int videoSocket = -1;
#endif
        tFramePacketQVGA pktFrm;

    public:
        QrRemoteCamera();
        virtual ~QrRemoteCamera();

        bool Connect(std::string addr, int port) override;
        bool Disconnect() override;
        bool Read(QrFrame& qrFrame, tTempUnit unit = tTempUnit::RAW) override;
    };
}


