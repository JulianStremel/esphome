#pragma once

#include "esphome/core/component.h"
#include "esphome/core/time.h"
#include "esphome/core/gpio.h"

namespace esphome {
namespace seven_segment {

class SEVENSEGMENTComponent;

using seven_segment_writer_t = std::function<void(SEVENSEGMENTComponent &)>;

class SEVENSEGMENTComponent : public PollingComponent {
 public:
  void set_writer(seven_segment_writer_t &&writer);

  void setup() override;

  void dump_config() override;

  void update() override;

  float get_setup_priority() const override;

  void display();

  // void set_num_chips(uint8_t num_chips);
  void set_a_pin(GPIOPin *a_pin);
  void set_b_pin(GPIOPin *b_pin);
  void set_c_pin(GPIOPin *c_pin);
  void set_d_pin(GPIOPin *d_pin);
  void set_e_pin(GPIOPin *e_pin);
  void set_f_pin(GPIOPin *f_pin);
  void set_g_pin(GPIOPin *g_pin);
  void set_dp_pin(GPIOPin *dp_pin);
  void set_g1_pin(GPIOPin *g1_pin);
  void set_g2_pin(GPIOPin *g2_pin);
  void set_g3_pin(GPIOPin *g3_pin);
  void set_g4_pin(GPIOPin *g4_pin);

  /// Evaluate the printf-format and print the result at the given position.
  uint8_t printf(uint8_t pos, const char *format, ...) __attribute__((format(printf, 3, 4)));
  /// Evaluate the printf-format and print the result at position 0.
  uint8_t printf(const char *format, ...) __attribute__((format(printf, 2, 3)));

  /// Print `str` at the given position.
  uint8_t print(uint8_t pos, const char *str);
  /// Print `str` at position 0.
  uint8_t print(const char *str);

  /// Evaluate the strftime-format and print the result at the given position.
  uint8_t strftime(uint8_t pos, const char *format, ESPTime time) __attribute__((format(strftime, 3, 0)));

  /// Evaluate the strftime-format and print the result at position 0.
  uint8_t strftime(const char *format, ESPTime time) __attribute__((format(strftime, 2, 0)));

 protected:
  void clear_display_();

  void set_digit_(uint8_t digit, uint8_t value, bool dp);

  GPIOPin *a_pin_{nullptr};
  GPIOPin *b_pin_{nullptr};
  GPIOPin *c_pin_{nullptr};
  GPIOPin *d_pin_{nullptr};
  GPIOPin *e_pin_{nullptr};
  GPIOPin *f_pin_{nullptr};
  GPIOPin *g_pin_{nullptr};
  GPIOPin *dp_pin_{nullptr};
  GPIOPin *g1_pin_{nullptr};
  GPIOPin *g2_pin_{nullptr};
  GPIOPin *g3_pin_{nullptr};
  GPIOPin *g4_pin_{nullptr};

  // uint8_t num_chips_{1};
  optional<seven_segment_writer_t> writer_{};
};

}  // namespace seven_segment
}  // namespace esphome