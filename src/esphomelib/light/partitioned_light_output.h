#ifndef ESPHOMELIB_PARTITIONED_LIGHT_OUTPUT_H
#define ESPHOMELIB_PARTITIONED_LIGHT_OUTPUT_H

#include "esphomelib/defines.h"
#include "esphomelib/helpers.h"
#include "esphomelib/light/light_state.h"
#include "esphomelib/power_supply_component.h"

#ifdef USE_NEO_PIXEL_BUS_LIGHT

#include "NeoPixelBus.h"

ESPHOMELIB_NAMESPACE_BEGIN

namespace light {

class PartitionableLightOutput : public LightOutput {
 public:
  virtual void write_partition(LightState *state, uint16_t index_start, uint16_t index_end) = 0;
  virtual LightTraits get_traits() = 0;

  void register_partition_state(LightState *state);

 protected:
  std::vector<LightState *> partitions_states_;
};

/** This component allows you to address the subset of a (NeoPixelBus) LED Strip and have it act as one light.
 */
class PartitionedLightOutputComponent : public LightOutput, public Component {
 public:
  PartitionedLightOutputComponent(PartitionableLightOutput *partitionable, LightState *master_state,
                                  uint16_t index_start, uint16_t index_end)
      : partitionable_(partitionable), master_state_(master_state), index_start_(index_start), index_end_(index_end) {}
  LightTraits get_traits() override;

  void write_state(LightState *state) override;

  void setup() override;
  void loop() override;
  float get_setup_priority() const override;

 private:
  PartitionableLightOutput *partitionable_;
  LightState *master_state_;
  uint16_t index_start_;
  uint16_t index_end_;
};
}  // namespace light
ESPHOMELIB_NAMESPACE_END
#endif
#endif
