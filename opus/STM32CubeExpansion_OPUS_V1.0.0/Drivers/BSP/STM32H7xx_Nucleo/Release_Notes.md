---
pagetitle: Release Notes for STM32H7xx_Nucleo BSP Drivers
lang: en
---

::: {.row}
::: {.col-sm-12 .col-lg-4}

::: {.card .fluid}
::: {.sectione .dark}
<center>
# **Release Notes for STM32H7xx_Nucleo BSP Drivers**
Copyright &copy; 2019 STMicroelectronics\
    
[![ST logo](_htmresc/st_logo.png)](https://www.st.com){.logo}
</center>
:::
:::

# License

This software component is licensed by ST under BSD 3-Clause license, the "License"; You may not use this component except in 
compliance with the License. You may obtain a copy of the License at:
<center>
[https://opensource.org/licenses/BSD-3-Clause](https://opensource.org/licenses/BSD-3-Clause)
</center>

# Purpose

The BSP (Board Specific Package) drivers are parts of the STM32Cube package based on the HAL drivers and provide a set of high level APIs relative to the hardware components and features in the evaluation boards, discovery kits and nucleo boards coming with the STM32Cube package for a given STM32 serie.


The BSP drivers allow a quick access to the boards’ services using high level APIs and without any specific configuration as the link with the HAL and the external components is done in intrinsic within the drivers. 


From project settings points of view, user has only to add the necessary driver’s files in the workspace and call the needed functions from examples. However some low level configuration functions are weak and can be overridden by the applications if user wants to change some BSP drivers default behavior.

:::

::: {.col-sm-12 .col-lg-8}
# Update History

::: {.collapse}
<input type="checkbox" id="collapse-section2" checked aria-hidden="true">
<label for="collapse-section2" aria-hidden="true">__V1.1.0 / 03-April-2020__</label>
<div>			

## Main Changes

-	Official release of STM32H7xx_Nucleo BSP drivers to support NUCLEO-H723ZG board 

## Dependencies

This software release is compatible with:

-   BSP common drivers __V7.0.0__ or above
-   STM32H7xx HAL drivers __V1.9.0__

</div>
:::

::: {.collapse}
<input type="checkbox" id="collapse-section1" checked aria-hidden="true">
<label for="collapse-section1" aria-hidden="true">__V1.0.0 / 30-October-2019__</label>
<div>			

## Main Changes

-	First official release of STM32H7xx_Nucleo BSP drivers in line with STM32Cube BSP drivers development guidelines (UM2298)

## Dependencies

This software release is compatible with:

-   BSP common drivers __V6.0.0__ or above
-   STM32H7xx HAL drivers __V1.7.0__

</div>
:::

:::
:::

<footer class="sticky">
For complete documentation on <mark>STM32 Microcontrollers</mark> ,
visit: [[www.st.com](http://www.st.com/STM32)]{style="font-color: blue;"}
</footer>
