#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

#if ((defined DEBUG_DEVELOPMENT) && (DEBUG_DEVELOPMENT == 1))
#include <Project_Settings_Devel.h>
#else
#include <Project_Settings_Release.h>
#endif

#include <Module_Settings.h>

#define DEVICE_CENTRAL_DISPLAY       1
#define DEVICE_LATERL_G    5

#define SYSTEM_BUILD_TYPE_RELEASE   0
#define SYSTEM_BUILD_TYPE_DEBUG     1

/* LIN NODE IDs **************************************************************** */
#define LIN_NODE_ID_STANDALONE_UI8  (uint8)0x0Au
#define LIN_NODE_ID_CLOCK_UI8       (uint8)0x20u
#define LIN_NODE_ID_OAT_UI8         (uint8)0x21u
#define LIN_NODE_ID_COMPASS_UI8     (uint8)0x27u
#define LIN_NODE_ID_STOPWATCH_UI8   (uint8)0x28u

#if 0
#define LIN_NODE_ID_LATERAL_G_UI8   (uint8)0xAAu
#endif

#define LIN_FRAME_ID_DATA_ZAE       (uint8)0x2Eu
#define LIN_FRAME_ID_ERR_ZAE        (uint8)0x2Du
#define LIN_FRAME_ID_DATA_NWSE      (uint8)0x32u
#define LIN_FRAME_ID_ERR_NWSE       (uint8)0x31u
#define LIN_FRAME_ID_DATA_UHR       (uint8)0x10u
#define LIN_FRAME_ID_ERR_UHR        (uint8)0x35u
#define LIN_FRAME_ID_DATA_CHRONO    (uint8)0x30u
#define LIN_FRAME_ID_ERR_CHRONO     (uint8)0x2Fu
#if 0
#define LIN_FRAME_ID_DATA_LAT_G     (uint8)0xu
#define LIN_FRAME_ID_ERR_LAT_G      (uint8)0xu
#endif

#endif /* PROJECT_SETTINGS_H */
