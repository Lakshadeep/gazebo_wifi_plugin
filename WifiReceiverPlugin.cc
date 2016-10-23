#include "WifiReceiverPlugin.hh"
#include "gazebo/sensors/SensorFactory.hh"
#include "gazebo/sensors/SensorManager.hh"
#include "gazebo/math/Rand.hh"
#include "gazebo/msgs/msgs.hh"
#include "gazebo/transport/Node.hh"
#include "gazebo/transport/Publisher.hh"
#include "gazebo/sensors/WirelessTransmitter.hh"

using namespace gazebo;
using namespace sensors;
GZ_REGISTER_SENSOR_PLUGIN(WifiReceiverPlugin)

WifiReceiverPlugin::WifiReceiverPlugin() : SensorPlugin()
{
}

WifiReceiverPlugin::~WifiReceiverPlugin()
{
}

void WifiReceiverPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/)
{
  // Get the parent sensor.
  this->parentSensor =
    std::dynamic_pointer_cast<sensors::WirelessReceiver>(_sensor);

  // Make sure the parent sensor is valid.
  if (!this->parentSensor)
  {
    gzerr << "WifiReceiverPlugin requires a Wireless Transmitter Sensor.\n";
    return;
  }

  // Connect to the sensor update event.
  this->updateConnection = this->parentSensor->ConnectUpdated(
      std::bind(&WifiReceiverPlugin::UpdateImpl, this));

  // Make sure the parent sensor is active.
  this->parentSensor->SetActive(true);
  // this->parentSensor->SetPose(ignition::math::Pose3d (100, 100, 100, 0, 0, 0));

}

bool WifiReceiverPlugin::UpdateImpl()
{
  std::string txEssid;
  // msgs::WirelessNodes msg;
  double rxPower;
  double txFreq;

  sensors::SensorPtr sensor_ptr;
  sensor_ptr = SensorManager::Instance()->GetSensor("wirelessTransmitter");

  sensors::WirelessTransmitterPtr transmitSensor;
  transmitSensor = std::dynamic_pointer_cast<sensors::WirelessTransmitter>(sensor_ptr);


  std::cout << "Connected to: " + transmitSensor->GetESSID() + "\n";
  double signal_strength;
  signal_strength = transmitSensor->SignalStrength(this->parentSensor->Pose(), this->parentSensor->Gain());
  std::cout << "Signal strengh: " << signal_strength << "\n";

  math::Pose myPos = this->parentSensor->Pose();
  std::cout << "Pose: " << myPos << "\n";


  /*for (Sensor_V::iterator it = sensors.begin(); it != sensors.end(); ++it)
  {
    if ((*it)->GetType() == "wireless_transmitter")
    {
      

      sensors::WirelessTransmitterPtr parentSensor;
      this->parentSensor = (*it)->GetSensor("wireless_transmitter");
      boost::shared_ptr<gazebo::sensors::WirelessTransmitter> transmitter =
           boost::static_pointer_cast<WirelessTransmitter>(*it);

      txFreq = transmitter->GetFreq();
      rxPower = transmitter->GetSignalStrength(myPos, this->GetGain());

      // Discard if the frequency received is out of our frequency range,
      // or if the received signal strengh is lower than the sensivity
      if ((txFreq < this->GetMinFreqFiltered()) ||
           (txFreq > this->GetMaxFreqFiltered()) ||
           (rxPower < this->GetSensitivity()))
      {
        continue;
      }

      txEssid = transmitter->GetESSID();

      msgs::WirelessNode *wirelessNode = msg.add_node();
      wirelessNode->set_essid(txEssid);
      wirelessNode->set_frequency(txFreq);
      std::cout << txEssid << "\n";
    }
  }*/


  return true;
      
}