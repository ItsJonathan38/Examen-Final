using UnityEngine;
using uPLibrary.Networking.M2Mqtt;
using System.Text;

public class PruebaMQTTRobot : MonoBehaviour
{
    MqttClient client;

    void Start()
    {
        client = new MqttClient("io.adafruit.com", 1883, false, null);

        string username = "ItsJonathan";
        string aioKey   = "AIO_KEY_AQUI";

        client.Connect("UnityClient", username, aioKey);
    }

    void Update()
    {
        if (!client.IsConnected) return;

        if (Input.GetKeyDown(KeyCode.Q)) Send("Q");
        if (Input.GetKeyDown(KeyCode.E)) Send("E");

        if (Input.GetKeyDown(KeyCode.A)) Send("A");
        if (Input.GetKeyDown(KeyCode.D)) Send("D");

        if (Input.GetKeyDown(KeyCode.W)) Send("W");
        if (Input.GetKeyDown(KeyCode.S)) Send("S");
    }

    void Send(string msg)
    {
        string topic = "ItsJonathan/feeds/eezybotarm";
        client.Publish(topic, Encoding.UTF8.GetBytes(msg));
        Debug.Log("Enviado: " + msg);
    }
}
