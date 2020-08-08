# radial_menu_ros

Radial menu on ROS1 for quick, accurate and intuitive selection by a joystick from 10+ items

![](https://raw.githubusercontent.com/yoshito-n-students/radial_menu_ros/images/images/screenshot_v0_1_4.png)

## Tested environments
* ROS Kinetic on Ubuntu 16.04
* ROS Melodic on Ubuntu 18.04
* ROS Noetic on Ubuntu 20.04

## Usage
* Subscribe both joy and menu state messages using [message_filters::TimeSynchronizer](http://wiki.ros.org/message_filters#Time_Synchronizer), watch which menu items are selected and process the joy messages when the menu is disabled (i.e. the menu does not own the joy messages). See an example node graph below or [example_teleop_node.cpp](radial_menu_example/src/example_teleop_node.cpp). The teleop_node in the graph can be replaced to your node.

![](https://raw.githubusercontent.com/yoshito-n-students/radial_menu_ros/images/images/example_integration_v0_2_1.png)

## Pkg: radial_menu_backend
### Nodelet: Backend
* Updates radial menu state based on joystick input

#### <u>Subscribed topics</u>
**joy** (sensor_msgs/Joy)

#### <u>Published topics</u>
**menu_state** ([radial_menu_msgs/State](radial_menu_msgs/msg/State.msg))
* The stamp in a message is copied from the source joy message

#### <u>Parameters</u>
**menu_description** (string, required)
* Tree structure of the menu in xml format like below
```XML
<!-- A simple example -->

<!-- An element must have the attribute 'name'.               -->
<!-- The 'name' of the root element indicates the menu title. -->
<item name="MoveCmd">
    <!-- An element can have child elements -->
    <item name="Front" />
    <item name="Left" />
    <item name="Back" />
    <item name="Right" />
</item>

<!-- Multiple root elements are not allowed -->
```
```XML
<!-- A complex example -->

<!-- An element can optionally have the attribute 'display'. -->
<!-- Possible values are;                                    -->
<!--   * 'name' (default): displays the item name            -->
<!--   * 'alttxt': displays an alternative text              -->
<!--   * 'image': displays an image                          -->
<item name="Reboot" display="alttxt" alttxt="&#xF021;">
    <item name="Base" display="image" imgurl="package://radial_menu_resources/images/base.bmp">
        <item name="Wheels" display="image" imgurl="file://Photos/wheels.png" />
        <item name="Cameras">
            <item name="Front" />
            ...
        </item>
    </item>
    <item name="Arm">
        ...
    </item>
</item>
```

**~allow_multi_selection** (bool, default: false)
* If false, current selected items will be deselected when a new item is selected

**~reset_on_enabling** (bool, default: false)
* If true, current selected items will be deselected when enabling the menu

**~reset_on_disabling** (bool, default: false)
* If true, current selected items will be deselected when disabling the menu

**~auto_select** (bool, default: false)
* If true, the last pointed item will be autonomously selected. Disable the menu before unpoint not to select.

**~enable_button** (int, default: 1)
* Button to keep enabling the menu
* PS4's circle button as default

**~select_button** (int, default: 5)
* Button to select or deselect an item, or descend the menu
* PS4's R1 button as default

**~ascend_button** (int, default: 4)
* Button to ascend the menu
* PS4's L1 button as default

**~pointing_axis_v** (int, default: 1)
* Vertical axis to point an item
* PS4's LEFT Y axis as default

**~pointing_axis_h** (int, default: 0)
* Horizontal axis to point an item
* PS4's LEFT X axis as default

**~invert_pointing_axis_v** (bool, default: false)

**~invert_pointing_axis_h** (bool, default: false)

**~pointing_axis_threshold** (double, default: 0.5)
* Threshold value of axis input to enable pointing

## Pkg: radial_menu_rviz
### Rviz plugin: RadialMenu
* Visualizes subscribed menu states as a radial menu
* Supports display types of items
* Shows the menu when the menu is being enabled

### Rviz plugin: HorizontalMenu
* Visualizes subscribed menu states as a single-lined menu 
* Displays the name of an item regardless of its display type
* Always shows the menu

## Pkg: radial_menu_model
* Contains an implementatin of menu tree model, which is commonly used in the backend and rviz packages

## Pkg: radial_menu_msgs
* Defines [State](radial_menu_msgs/msg/State.msg) message type

## Pkg: radial_menu
* A meta-package depending radial_menu_backend, radial_menu_model, radial_menu_rviz, radial_menu_msgs for future release

## Pkg: radial_menu_example
* Provides a [full example](radial_menu_example/launch/example_full.launch) which requires a joystick and a [Rviz frontend example](radial_menu_example/launch/example_rviz.launch) which does not
* Examples use the font 'FontAwesome' to display emojis. Install it by `sudo apt install fonts-font-awesome` 