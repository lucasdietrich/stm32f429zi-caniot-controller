# SDMMC (external SD flash disk)

- STM32 drivers : `drivers\disk\sdmmc_stm32.c`
        - [zephyr/ext/hal/st/stm32cube/stm32f4xx/drivers/src/stm32f4xx_ll_sdmmc.c](https://github.com/intel/zephyr/blob/master/ext/hal/st/stm32cube/stm32f4xx/drivers/src/stm32f4xx_ll_sdmmc.c)
- [devicetree - st,stm32-sdmmc](https://docs.zephyrproject.org/latest/reference/devicetree/bindings/mmc/st%2Cstm32-sdmmc.html)


Configuration options : 
  - [CONFIG_SDMMC_STM32](https://docs.zephyrproject.org/latest/reference/kconfig/CONFIG_SDMMC_STM32.html#std-kconfig-CONFIG_SDMMC_STM32)
    - selects `CONFIG_USE_STM32_LL_SDMMC`
  - `CONFIG_SDMMC_LOG_LEVEL_DBG`
  - [CONFIG_SDMMC_VOLUME_NAME](https://docs.zephyrproject.org/latest/reference/kconfig/CONFIG_SDMMC_VOLUME_NAME.html#std-kconfig-CONFIG_SDMMC_VOLUME_NAME)
  - [CONFIG_SDMMC_OVER_SPI](https://docs.zephyrproject.org/latest/reference/kconfig/CONFIG_SDMMC_OVER_SPI.html)
  - `CONFIG_DISK_DRIVER_SDMMC`