#pragma once

namespace QrSDK
{
#define QR_PAYLOAD_SIZE 8
#define QR_PACKET_SIZE  14

    namespace QrProtocol
    {
        typedef enum PROTOCOLMODE : uint8_t
        {
            MODE_NORMAL         = 0x01,
            MODE_STATISTICS     = 0x02,
            MODE_PACKET         = 0x03
        } tProtocolMode;

        typedef enum CTRLCODE : uint8_t
        {
            CTRL_SOH        = 0x01,    // Start of Header
            CTRL_STX        = 0x02,    // Start of Text
            CTRL_ETX        = 0x03,    // End of Text
            CTRL_EOT        = 0x04,    // End of Transmission
            CTRL_ENQ        = 0x05,    // Enquiry

            CTRL_CR         = 0x0D,    // carrige return
            CTRL_LF         = 0x0A,    // line feed

            CTRL_ACK        = 0x06,    // acknowlege
            CTRL_NACK       = 0x15,   // negative acknowlege
            CTRL_SYNC       = 0x16,   // Synchronous Idle
            CTRL_ETB        = 0x17     // End of Transmission Block

        } tCtrlCode;

        typedef enum PKT_TX_INDEX : int
        {
            IDX_TX_STX      = 0,    // STX
            IDX_TX_SRC      = 1,    // Source
            IDX_TX_DST      = 2,    // Destination
            IDX_TX_HDR      = 3,    // Header
            IDX_TX_DATA0    = 4,    // DATA0
            IDX_TX_DATA1    = 5,    // DATA1
            IDX_TX_CRC      = 12,   // CRC
            IDX_TX_ETX      = 13    // ETX

        } tPacketTxIndex;

        typedef enum PACKET_RX_INDEX : int
        {
            IDX_PKT_RX_STX      = 0,    // STX
            IDX_PKT_RX_SRC      = 1,    // Source
            IDX_PKT_RX_DEST     = 2,    // Destination
            IDX_PKT_RX_LEN      = 3,    // Length
            IDX_PKT_RX_HDR      = 4,    // Header
            IDX_PKT_RX_DATA     = 5,    // Payload Data
            IDX_PKT_RX_RC       = 11,   // Return Code
            IDX_PKT_RX_CRC      = 12,   // CRC
            IDX_PKT_RX_EOF      = 13    // EOF

        } tPacketRxIndex;

        typedef enum NETWORK_RX_INDEX : int
        {
            IDX_NET_RX_SYNC     = 0,    // SYNC
            IDX_NET_RX_STX      = 1,    // STX
            IDX_NET_RX_SRC      = 2,    // Source
            IDX_NET_RX_DEST     = 3,    // Destination
            IDX_NET_RX_HDR      = 4,    // Header ?
            IDX_NET_RX_DATA     = 5,    // Payload
            IDX_NET_RX_CRC      = 13,   // CRC
            IDX_NET_RX_EOF      = 14    // EOF

        } tNetworkRxIndex;

        typedef enum CMD_SRC : uint8_t
        {
            SRC_OTHER       = 0x00,
            SRC_PACKET      = 0x01,
            SRC_TERMINAL    = 0x02
        } tCmdSrc;

        typedef enum CMD_DST : uint8_t
        {
            DST_EOST        = 0x03, // 측정용
            DST_BOTH        = 0x04, // SURV & EOST
            DST_SURV        = 0x06, // 관측용
            DST_NETWORK     = 0x09, // Network board
            DST_VIDEO       = 0x0C  // camera video
        } tCmdDst;

        typedef enum GAIN_MODE : uint8_t
        {
            GAIN_HIGH       = 0x00, // High Gain
            GAIN_LOW        = 0x01, // Low Gain
            GAIN_NONE       = 0xFF  // 
        } tGainMode;

        typedef enum AUTO_SHUTTER : uint8_t
        {
            SHUTTER_OFF     = 0x00, // Disable AutoShutter
            SHUTTER_ON      = 0x01,
            SHUTTER_NONE    = 0xFF
        } tAutoShutter;

        typedef enum SHUTTER_COMP : uint8_t
        {
            SHUTTER_COMP_ON = 0x00,
            SHUTTER_COMP_OFF = 0x01,
            SHUTTER_COMP_NONE = 0xFF
        } tShutterComp;

        typedef enum SHUTTER_CTRL : uint8_t
        {
            SHUTTER_OPEN    = 0x01,
            SHUTTER_CLOSE   = 0x02,
        } tCtrlShutter;

        typedef enum ALARM_NUC : uint8_t
        {
            ALARM_OFF       = 0xA1,
            ALARM_ON        = 0xA0,
            ALARM_NONE      = 0xFF
        } tAlarmNUC;

        typedef enum TEMP_CVRT : uint8_t
        {
            TEMP_CVRT_ON    = 0x00,
            TEMP_CVRT_OFF   = 0x01,
            TEMP_CVRT_NONE  = 0xFF
        } tTempConvert;

        typedef enum TRSM_COMP : uint8_t
        {
            TRSM_COMP_ON    = 0x04,
            TRSM_COMP_OFF   = 0x05,
            TRSM_COMP_NONE  = 0xFF
        } tTrsmComp;

        typedef enum TRSM_GUIDE : uint8_t
        {
            TRSM_GUIDE_ON   = 0x01,
            TRSM_GUIDE_OFF  = 0x00,
            TRSM_GUIDE_NONE = 0xFF,
        } tTrsmGuide;

        typedef enum TRSM_GUIDE_TO : uint8_t
        {
            TRSM_GUIDE_TO_LEFT  = 0x00,
            TRSM_GUIDE_TO_RIGHT = 0x01,
            TRSM_GUIDE_TO_UP    = 0x02,
            TRSM_GUIDE_TO_DOWN  = 0x03,
            TRSM_GUIDE_TO_NONE  = 0xFF,
        } tTrsmGuideTo;

        typedef enum TEMP_PRINT : uint8_t
        {
            TEMP_PRT_ON     = 0x05,
            TEMP_PRT_OFF    = 0x06,
            TEMP_PRT_NONE   = 0xFF,
        } tTempPrint;
        /// <summary>
        /// IP Mode
        /// </summary>
        typedef enum IP_MODE : uint8_t
        {
            IP_STATIC       = 0x00,
            IP_DHCP         = 0x01,
            IP_NONE         = 0xFF
        } tIpMode;

        /// <summary>
        ///  Hot Mode
        /// </summary>
        typedef enum HOT_MODE : uint8_t
        {
            HOT_WHITE       = 0x00,
            HOT_BLACK       = 0x01,
            HOT_NONE        = 0xFF
        } tHotMode;

        /// <summary>
        ///  View Mode
        /// </summary>
        typedef enum VIEW_MODE : uint8_t
        {
            VIEW_NUC        = 0x02,
            VIEW_RAW        = 0x03,
            VIEW_PATTERN    = 0x04
        } tViewMode;

        /// <summary>
        /// Control TEC
        /// </summary>
        typedef enum TEC_CTRL : uint8_t
        {
            TEC_ON          = 0x05,
            TEC_OFF         = 0x06
        } tCtrlTEC;

        /// <summary>
        /// Dead Pixel Compensation
        /// </summary>
        typedef enum DPC_CTRL : uint8_t
        {
            DPC_ON = 0x00,
            DPC_OFF = 0x01
        } tCtrlDPC;

        /// <summary>
        /// 2nd Compensation
        /// </summary>
        typedef enum COMP_CTRL : uint8_t
        {
            COMP_ON = 0x03,
            COMP_OFF = 0x04
        } tCtrlComp;

        /// <summary>
        /// Dual Ouput
        /// </summary>
        typedef enum IMG_OUT : uint8_t
        {
            IMG_FIRST = 0x20,
            IMG_LAST = 0x21
        } tImageOut;


    };
}
