#include "WifiRouterPlugin.hh"

using namespace gazebo;
GZ_REGISTER_SENSOR_PLUGIN(WifiRouterPlugin)

WifiRouterPlugin::WifiRouterPlugin() : SensorPlugin()
{
}

WifiRouterPlugin::~WifiRouterPlugin()
{
}

void WifiRouterPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/)
{
  // Get the parent sensor.
  this->parentSensor =
    std::dynamic_pointer_cast<sensors::WirelessTransmitter>(_sensor);

  // Make sure the parent sensor is valid.
  if (!this->parentSensor)
  {
    gzerr << "WifiRouterPlugin requires a Wireless Transmitter Sensor.\n";
    return;
  }

  // Connect to the sensor update event.
  this->updateConnection = this->parentSensor->ConnectUpdated(
      std::bind(&WifiRouterPlugin::OnUpdate, this));

  // Make sure the parent sensor is active.
  this->parentSensor->SetActive(true);

  std::string essid;
  essid = this->parentSensor->GetESSID ();

  std::cout << " ESSID:" << essid << "\n";
}

void WifiRouterPlugin::OnUpdate()
{
  std::string essid;
  essid = this->parentSensor->GetESSID ();
  // std::cout << " ESSID:" << essid << "\n";
}