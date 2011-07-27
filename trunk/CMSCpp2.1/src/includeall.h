//#define LCD_DEVICE

#include "config.h"
#include <math/include.h>
#include <cms/include.h>
#include <cms/util/include.h>
#include <cms/measure/include.h>

#ifdef LCD_DEVICE
#include <cms/lcd/include.h>
#include <cms/devicemodel/include.h>
#include <cms/lcd/calibrate/include.h>
#endif

#include <cms/colorspace/include.h>
#include <cms/colorformat/include.h>
#include <cms/hsv/include.h>
#include <i2c/include.h>
#include <java/lang.h>
#include <vcl.h>
#include <debug.h>
#include <gui/util/binder.h>
#include <gui/event/listener.h>
#include <algo/minimisation.h>


 