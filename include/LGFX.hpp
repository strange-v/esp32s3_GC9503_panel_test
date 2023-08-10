#ifndef LGFX_H
#define LGFX_H

#include <LovyanGFX.hpp>
#include <lgfx/v1/platforms/esp32s3/Panel_RGB.hpp>
#include <lgfx/v1/platforms/esp32s3/Bus_RGB.hpp>

class LGFX : public lgfx::LGFX_Device
{
public:
  lgfx::Bus_RGB _bus_instance;
  lgfx::Panel_GC9503 _panel_instance;
  lgfx::Touch_FT5x06 _touch_instance;
  lgfx::Light_PWM _light_instance;

  LGFX(void)
  {
    {
      auto cfg = _panel_instance.config();

      cfg.memory_width = TFT_WIDTH;
      cfg.memory_height = TFT_HEIGHT;
      cfg.panel_width = TFT_WIDTH;
      cfg.panel_height = TFT_HEIGHT;

      cfg.offset_x = 0;
      cfg.offset_y = 0;

      cfg.pin_rst = TFT_VSYNC;

      _panel_instance.config(cfg);
    }

    {
      auto cfg = _panel_instance.config_detail();

      cfg.pin_cs = TFT_CS;
      cfg.pin_sclk = TFT_SCLK;
      cfg.pin_mosi = TFT_MOSI;

      _panel_instance.config_detail(cfg);
    }

    {
      auto cfg = _bus_instance.config();
      cfg.panel = &_panel_instance;
      cfg.pin_d0 = TFT_D0;   // B0
      cfg.pin_d1 = TFT_D1;   // B1
      cfg.pin_d2 = TFT_D2;   // B2
      cfg.pin_d3 = TFT_D3;   // B3
      cfg.pin_d4 = TFT_D4;   // B4
      cfg.pin_d5 = TFT_D5;   // G0
      cfg.pin_d6 = TFT_D6;   // G1
      cfg.pin_d7 = TFT_D7;   // G2
      cfg.pin_d8 = TFT_D8;   // G3
      cfg.pin_d9 = TFT_D9;   // G4
      cfg.pin_d10 = TFT_D10; // G5
      cfg.pin_d11 = TFT_D11; // R0
      cfg.pin_d12 = TFT_D12; // R1
      cfg.pin_d13 = TFT_D13; // R2
      cfg.pin_d14 = TFT_D14; // R3
      cfg.pin_d15 = TFT_D15; // R4

      cfg.pin_henable = TFT_DE;
      cfg.pin_vsync = TFT_VSYNC;
      cfg.pin_hsync = TFT_HSYNC;
      cfg.pin_pclk = TFT_PCLK;
      cfg.freq_write = 15000000;

      cfg.hsync_polarity = 1;
      cfg.hsync_front_porch = 8;
      cfg.hsync_pulse_width = 10;
      cfg.hsync_back_porch = 50;
      cfg.vsync_polarity = 1;
      cfg.vsync_front_porch = 8;
      cfg.vsync_pulse_width = 10;
      cfg.vsync_back_porch = 20;
      cfg.pclk_idle_high = 0;
      cfg.de_idle_high = 0;
      cfg.pclk_active_neg = 0;

      _bus_instance.config(cfg);
    }
    _panel_instance.setBus(&_bus_instance);

    {
      auto cfg = _touch_instance.config();
      cfg.x_min = 0;
      cfg.x_max = TFT_WIDTH - 1;
      cfg.y_min = 0;
      cfg.y_max = TFT_HEIGHT - 1;
      cfg.bus_shared = false;
      cfg.offset_rotation = 0;

      // cfg.i2c_port = I2C_NUM_1;

      cfg.pin_int = TOUCH_IRQ;
      cfg.pin_sda = TOUCH_SDA;
      cfg.pin_scl = TOUCH_SCL;
      cfg.pin_rst = TOUCH_RST;

      cfg.freq = I2C_TOUCH_FREQUENCY;
      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);
    }

    {
      auto cfg = _light_instance.config();
      cfg.pin_bl = TFT_BCKL;
      _light_instance.config(cfg);
    }
    _panel_instance.light(&_light_instance);

    setPanel(&_panel_instance);
  }
};
#endif