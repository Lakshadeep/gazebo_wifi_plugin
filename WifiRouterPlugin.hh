#ifndef _GAZEBO_WIFI_ROUTER_PLUGIN_HH_
#define _GAZEBO_WIFI_ROUTER_PLUGIN_HH_

#include <string>

#include <gazebo/gazebo.hh>
#include <gazebo/sensors/sensors.hh>

namespace gazebo
{
  class WifiRouterPlugin : public SensorPlugin
  {
    /// \brief Constructor.
    public: WifiRouterPlugin();

    /// \brief Destructor.
    public: virtual ~WifiRouterPlugin();

    /// \brief Load the sensor plugin.
    /// \param[in] _sensor Pointer to the sensor that loaded this plugin.
    /// \param[in] _sdf SDF element that describes the plugin.
    public: virtual void Load(sensors::SensorPtr _sensor, sdf::ElementPtr _sdf);

    private: virtual void OnUpdate();

    private: sensors::WirelessTransmitterPtr parentSensor;

    private: event::ConnectionPtr updateConnection;
  };
}
#endif