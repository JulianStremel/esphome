import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import display
from esphome.const import CONF_ID, CONF_LAMBDA, CONF_NUM_DIGITS

seven_segment_ns = cg.esphome_ns.namespace("seven_segment")
SEVENSEGMENTComponent = seven_segment_ns.class_(
    "SEVENSEGMENTComponent", cg.PollingComponent
)
SEVENSEGMENTComponentRef = SEVENSEGMENTComponent.operator("ref")

CONF_REVERSE_ENABLE = "reverse_enable"

CONFIG_SCHEMA = (
    display.BASIC_DISPLAY_SCHEMA.extend(
        {
            cv.GenerateID(): cv.declare_id(SEVENSEGMENTComponent),
            cv.Required(CONF_A_PIN): cv.gpio_output_pin_schema,
            cv.Required(CONF_B_PIN): cv.gpio_output_pin_schema,
            cv.Required(CONF_C_PIN): cv.gpio_output_pin_schema,
            cv.Required(CONF_D_PIN): cv.gpio_output_pin_schema,
            cv.Required(CONF_E_PIN): cv.gpio_output_pin_schema,
            cv.Required(CONF_F_PIN): cv.gpio_output_pin_schema,
            cv.Required(CONF_G_PIN): cv.gpio_output_pin_schema,
            cv.Optional(CONF_DP_PIN): cv.gpio_output_pin_schema,
            cv.Optional(CONF_NUM_DIGITS, default=1): cv.int_range(min=1, max=255),
            

        }
    )
    .extend(cv.polling_component_schema("1s"))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await display.register_display(var, config)

    cg.add(var.set_num_chips(config[CONF_NUM_DIGITS]))

    if CONF_LAMBDA in config:
        lambda_ = await cg.process_lambda(
            config[CONF_LAMBDA], [(SEVENSEGMENTComponentRef, "it")], return_type=cg.void
        )
        cg.add(var.set_writer(lambda_))
