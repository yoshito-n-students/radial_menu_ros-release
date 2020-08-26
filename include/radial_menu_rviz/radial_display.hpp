#ifndef RADIAL_MENU_RVIZ_RADIAL_DISPLAY_HPP
#define RADIAL_MENU_RVIZ_RADIAL_DISPLAY_HPP

#include <radial_menu_rviz/display_base.hpp>
#include <radial_menu_rviz/properties.hpp>
#include <radial_menu_rviz/radial_image_drawer.hpp>
#include <radial_menu_rviz/radial_property_control.hpp>

#include <QObject>

namespace radial_menu_rviz {

class RadialDisplay
    : public DisplayBase< RadialDrawingProperty, RadialPropertyControl, RadialImageDrawer > {
  Q_OBJECT

private:
  typedef DisplayBase< RadialDrawingProperty, RadialPropertyControl, RadialImageDrawer > Base;

public:
  RadialDisplay() {}

  virtual ~RadialDisplay() {}

protected:
  // called once on initialization
  virtual void onInitialize() {
    Base::onInitialize();

    // origin in the position property indicates the image center
    overlay_->setAlignment(Qt::AlignCenter);

    // slots on properties changed
    connect(prop_ctl_.get(), &RadialPropertyControl::descriptionPropertyChanged, this,
            &RadialDisplay::updateDescription);
    connect(prop_ctl_.get(), &RadialPropertyControl::subscriptionPropertyChanged, this,
            &RadialDisplay::updateSubscription);
    connect(prop_ctl_.get(), &RadialPropertyControl::drawingPropertyChanged, this,
            &RadialDisplay::updateImage);
    connect(prop_ctl_.get(), &RadialPropertyControl::positionPropertyChanged, this,
            &RadialDisplay::updatePosition);
  }

protected Q_SLOTS:
  void updateDescription(const DescriptionProperty &prop) { Base::updateDescription(prop); }

  void updateSubscription(const SubscriptionProperty &prop) { Base::updateSubscription(prop); }

  void updateImage(const RadialDrawingProperty &prop) { Base::updateImage(prop); }

  void updatePosition(const PositionProperty &prop) { Base::updatePosition(prop); }
};
} // namespace radial_menu_rviz

#endif