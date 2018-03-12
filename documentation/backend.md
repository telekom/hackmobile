# Backend

There is a backend which can be used to query the data of the calliope board. There are also two ways to querying the data. For the history data there is a REST interface and for the "realtime" data is a MQTT endpoint available.

***Please note:*** Due to the high latency of the NB-IoT network the data will not send within a short time frame. There will always a noticeable delay until the data will be available with the REST or the MQTT API. The minimum will be 1.6s-10.0s seconds or even more. (source Wikipedia: [NarrowBand IoT](https://en.wikipedia.org/wiki/NarrowBand_IOT))

## What do you need to do?
To get all needed informations about your account and recieve the sended data there are several steps requirered:
* Open the [WEB GUI](http://ubirch.demo.ubirch.com/#!/login)
* Login with your existing Google Account or Create a new "Ubirch" Account (you can create an account an the "ubirch" [login site](https://id.dev.ubirch.com/auth/realms/ubirch/protocol/openid-connect/auth?response_type=code&client_id=ubirch-admin-ui-demo))
* Get your deviceId from the calliope board
* Create a new Device in the GUI
* Get all needed informations (tokens, endpoints and so on)

The description for all these steps are noted down in the next topics.

## How to get the deviceID / hardwareID from your Calliope Board
To get the ```deviceID``` for your Calliope Board you must first get the ```hardwareID``` from the board itself. To get the ```hardwareID``` just install the [deviceInfo demo hex](https://raw.githubusercontent.com/ubirch/telekom-nbiot-hackathon-2017/master/deviceinfo.hex) on your calliope board.   
  
After the file successfully installed there will be a [HEX number](https://en.wikipedia.org/wiki/Hexadecimal) presented on the 5x5 LED matrix (e.g. ```AB12CD34```, please write down the hex number).  

After you successfully got the ```hardwareID``` login into the [WEB GUI](http://ubirch.demo.ubirch.com/#!/login) with the provided login credentials. Click than "Add Device" and copy&paste the ```hardwareID (hex number)``` you wrote down before and click save. The device is now registered with the backend and you can get the data from the MQTT endpoint or the REST API.  

The ```deviceID``` that is needed for all requests can be found in the detail site of the device you just added. Just click on your device in the [device list of the WEB GUI](http://ubirch.demo.ubirch.com/#!/devices-list) and in the detail site under ```settings``` and ```developer information``` all needed information for the ```oAuthtoken```, ```deviceID``` and so on are provided there.

There is also the ability to sing the data with a ecc key. More information about the optional signing can be found [here](https://github.com/ubirch/telekom-nbiot-hackathon-2017/blob/master/de-pxt-development.md#geheimen-schlüssel-erzeugen-optional) 

## WEB GUI Shortcuts:
* [Login](http://ubirch.demo.ubirch.com/#!/login)
* [Device list](http://ubirch.demo.ubirch.com/#!/devices-list)
* [REST Docu](http://developer.ubirch.com/docs/api/swagger-ui.html)

# REST
> Representational state transfer (REST) or RESTful web services is a way of providing interoperability between computer systems on the Internet. REST-compliant Web services allow requesting systems to access and manipulate textual representations of Web resources using a uniform and predefined set of stateless operations.  
source: Wikipedia [REST](https://en.wikipedia.org/wiki/Representational_state_transfer)

We also prepared a [Postman](https://www.getpostman.com) collection for each request for you. [Postman](https://www.getpostman.com) is:
> A powerful GUI platform to make your API development faster & easier, from building API requests through testing, documentation and sharing.

The collection than be downloaded from [here](documents/dthack17_REST_API.postman_collection)

### URL's / Endpoints / Tokens
The base URL (called apiURL in the following examples) for all of the REST calls can be found in the tab "Dev Info's" on the detail site of a defive in the [WebGUI](https://ubirch.demo.ubirch.com/#!/devices-list):
* ```https://api.ubirch.demo.ubirch.com```

### Authorization
For all of the REST calls there is a auth header needed with the provided oAuth Bearer token. The auth header should be formatted as followed:
* **Name/Key of the header field:** ```authorization```
* **Format of the value:**  ```Bearer 'oAuthtoken'``` e.g. ```Bearer ya29.GlyuBBaWNXuMkcLQaaKj47XRLL6nzt-cIMequoS9mhqoNFyDA289Elhapr2A-3EI-cPArWFW03_zvQPQc8rjkrCSq5XhP0q7nmqFI1A5mV2vRMYlo0mexYRHgZX5Vw```

## Methods
There are six different request formats to get the data for a specific board. Please note that the response for all of the different requests has the same format.
## Device Data
Gets all recent data for a specific device (e.g. Calliope Board) that was send to the backend.
**Request URL:** ```{{apiURL}}/api/avatarService/v1/device/{{deviceID}}/data/history```
**Parameters**
  * apiURL: is the URL for the REST endpoint (see above)
  * deviceID: is the deviceID for your calliope board (see above how to get the deviceId from your board)  

**Example Request**
  * apiURL: ```https://api.ubirch.demo.ubirch.com```
  * deviviceID: ```a425081d-0737-4e0c-84ba-7137d57b4b10```
  * oAuthTokne: ```ya29.GlyuBBaWNXuMkcLQaaKj47XRLL6nzt-cIMequoS9mhqoNFyDA289Elhapr2A-3EI-cPArWFW03_zvQPQc8rjkrCSq5XhP0q7nmqFI1A5mV2vRMYlo0mexYRHgZX5Vw```

**Request:**
```bash
curl -X GET \
  https://api.ubirch.demo.ubirch.com/api/avatarService/v1/device/a425081d-0737-4e0c-84ba-7137d57b4b10/data/history \
  -H 'authorization: Bearer ya29.GlyuBBaWNXuMkcLQaaKj47XRLL6nzt-cIMequoS9mhqoNFyDA289Elhapr2A-3EI-cPArWFW03_zvQPQc8rjkrCSq5XhP0q7nmqFI1A5mV2vRMYlo0mexYRHgZX5Vw'
```

**Response:**
```JSON
[
    {
        "messageId": "1c224044-451b-4064-a2dd-3eb783332a38",
        "deviceDataRawId": "ed3cb8ca-0a5e-4dda-8d67-7c6f87df8469",
        "deviceId": "a425081d-0737-4e0c-84ba-7137d57b4b10",
        "deviceName": "envSensor 05",
        "deviceType": "envSensor",
        "deviceTags": [
            "ubirch#1",
            "sensor",
            "btcDemo"
        ],
        "deviceMessage": {
            "temperature": 25.82,
            "presure": 9.99,
            "humidity": 41.13,
            "batteryLevel": 100,
            "latitude": 13.3643,
            "longitude": 52.481083,
            "loops": -709,
            "altitude": 25922.2,
            "errorCode": 0,
            "timestamp": "2017-09-10T08:39:54.002Z"
        },
        "deviceDataRaw": {
            "id": "ed3cb8ca-0a5e-4dda-8d67-7c6f87df8469",
            "v": "0.0.3",
            "fw": "V.3.1",
            "a": "3PwbZg4fmrM715+dCPlZr0Y6lsy5qHFpN/0cGZcZXNdoy8TDehWN4M9Ph+xUBSR5QviaL0Kz97VzDRRMXVPoaA==",
            "ts": "2017-09-10T08:10:53.848Z",
            "k": "OIX0hvZpHPKiWQRgOFhA6oYOMK6mT6mldtoyg578cPs=",
            "s": "7sn+ts5veknaj1KIH6oS5cvmaOyw86oQoSHCCULrfRRHOxRmwaKlru2S+ZJasFbqHodwe5V8mNyF0gAFsP/qDg==",
            "p": [
                {
                    "t": 2584,
                    "p": 999,
                    "h": 4109,
                    "a": 2592220,
                    "la": "13.36430",
                    "lo": "52.481083",
                    "ba": 100,
                    "lp": -717,
                    "e": 0,
                    "aq": 630,
                    "aqr": 530,
                    "ts": "2017-9-10T8:38:11.2Z"
                },
...
...
...
```

## Device Data with Page
The request is the same as the ```Device Data``` request, except that you can request the data with pages aka pagination.
**Request URL:** ```{{apiURL}}/api/avatarService/v1/device/{{deviceID}}/data/history/{{from}}/{{pagesize}}```
**Parameters**
  * apiURL and deviceID: same as with the ```Device Data``` request
  * from: the page where the response should be startet from (an integer that is greater or equal to zero)
  * pagesize: how many results should be returned (an integer that is greater or equal to zero)

**Example Request**
  * apiURL, deviviceID and oAuthToken: same as with the ```Device Data``` request
  * from: ```5```
  * pagesize: ```1```

**Request:**
```bash
curl -X GET \
  https://api.ubirch.demo.ubirch.com/api/avatarService/v1/device/a425081d-0737-4e0c-84ba-7137d57b4b10/data/history/5/1 \
  -H 'authorization: Bearer ya29.GlyuBBaWNXuMkcLQaaKj47XRLL6nzt-cIMequoS9mhqoNFyDA289Elhapr2A-3EI-cPArWFW03_zvQPQc8rjkrCSq5XhP0q7nmqFI1A5mV2vRMYlo0mexYRHgZX5Vw'
```

**Response:**
Same as with the ```Device Data``` request, except that there is only one item returned

## Device Data by date
The request is the same as the ```Device Data``` request, except that you can request the data for a specific date.
**Request URL:** ```{{apiURL}}/api/avatarService/v1/device/{{deviceID}}/data/history/byDate/from/{{fromDate}}/to/{{toDate}}```
**Parameters**
  * apiURL and deviceID: same as with the ```Device Data``` request
  * fromDate: the start date for the request. May be in the [ISO 8601](https://en.wikipedia.org/wiki/ISO_8601) e.g. ```yyyy-MM-dd’T’HH:mm:ssZ```
  * toDate: the end date for the request. Should be also in the same format as the ```fromDate```. The ```toDate``` should be equal or greater than the ```fromDate```.

**Example Request**
  * apiURL, deviviceID and oAuthToken: same as with the ```Device Data``` request
  * fromDate: ```2017-08-21T12:17:07.002Z```
  * toDate: ```2017-08-21T12:17:07.002Z```

**Request:**
```bash
curl -X GET \
  https://api.ubirch.demo.ubirch.com/api/avatarService/v1/device/a425081d-0737-4e0c-84ba-7137d57b4b10/data/history/byDate/from/2017-08-21T12:17:07.002Z/to/2017-08-21T12:17:07.002Z \
  -H 'authorization: Bearer ya29.GlyuBBaWNXuMkcLQaaKj47XRLL6nzt-cIMequoS9mhqoNFyDA289Elhapr2A-3EI-cPArWFW03_zvQPQc8rjkrCSq5XhP0q7nmqFI1A5mV2vRMYlo0mexYRHgZX5Vw'
```

**Response:**
Same as with the ```Device Data``` request, with data in the give timeframe

## Device Data after a date
The request is the same as the ```Device Data``` request, except that you can request the data after a specific date.
**Request URL:** ```{{apiURL}}/api/avatarService/v1/device/{{deviceID}}/data/history/byDate/after/{{afterDate}}```
**Parameters**
  * apiURL and deviceID: same as with the ```Device Data``` request
  * afterDate: the start date for the request. May be in the [ISO 8601](https://en.wikipedia.org/wiki/ISO_8601) e.g. ```yyyy-MM-dd’T’HH:mm:ssZ```

**Example Request**
  * apiURL, deviviceID and oAuthToken: same as with the ```Device Data``` request
  * afterDate: ```2017-08-21T12:17:07.002Z```

**Request:**
```bash
curl -X GET \
  https://api.ubirch.demo.ubirch.com/api/avatarService/v1/device/a425081d-0737-4e0c-84ba-7137d57b4b10/data/history/byDate/after/2017-09-14T11:00:03.002Z \
  -H 'authorization: Bearer ya29.GlyuBBaWNXuMkcLQaaKj47XRLL6nzt-cIMequoS9mhqoNFyDA289Elhapr2A-3EI-cPArWFW03_zvQPQc8rjkrCSq5XhP0q7nmqFI1A5mV2vRMYlo0mexYRHgZX5Vw'
```

**Response:**
Same as with the ```Device Data``` request, with data after the give date

## Device Data before a date
The request is the same as the ```Device Data``` request, except that you can request the data before a specific date.
**Request URL:** ```{{apiURL}}/api/avatarService/v1/device/{{deviceID}}/data/history/byDate/before/{{beforeDate}}```
**Parameters**
  * apiURL and deviceID: same as with the ```Device Data``` request
  * beforeDate: the end date for the request. May be in the [ISO 8601](https://en.wikipedia.org/wiki/ISO_8601) e.g. ```yyyy-MM-dd’T’HH:mm:ssZ```

**Example Request**
  * apiURL, deviviceID and oAuthToken: same as with the ```Device Data``` request
  * beforeDate: ```2017-08-21T12:17:07.002Z```

**Request:**
```bash
curl -X GET \
  https://api.ubirch.demo.ubirch.com/api/avatarService/v1/device/a425081d-0737-4e0c-84ba-7137d57b4b10/data/history/byDate/before/2017-08-21T12:17:07.002Z \
  -H 'authorization: Bearer ya29.GlyuBBaWNXuMkcLQaaKj47XRLL6nzt-cIMequoS9mhqoNFyDA289Elhapr2A-3EI-cPArWFW03_zvQPQc8rjkrCSq5XhP0q7nmqFI1A5mV2vRMYlo0mexYRHgZX5Vw'
```

**Response:**
Same as with the ```Device Data``` request, with data before the give date

## Device Data for a day
The request is the same as the ```Device Data``` request, except that you can request the data for a specific day.
**Request URL:** ```{{apiURL}}/api/avatarService/v1/device/{{deviceID}}/data/history/byDate/day/{{dayDate}}```
**Parameters**
  * apiURL and deviceID: same as with the ```Device Data``` request
  * dayDate: the day for the request. May be in the [ISO 8601](https://en.wikipedia.org/wiki/ISO_8601) e.g. ```yyyy-MM-dd’T’HH:mm:ssZ```

**Example Request**
  * apiURL, deviviceID and oAuthToken: same as with the ```Device Data``` request
  * dayDate: ```2017-08-21T12:17:07.002Z```

**Request:**
```bash
curl -X GET \
  https://api.ubirch.demo.ubirch.com/api/avatarService/v1/device/a425081d-0737-4e0c-84ba-7137d57b4b10/data/history/byDate/day/2017-08-21T12:20:07.002Z \
  -H 'authorization: Bearer ya29.GlyuBBaWNXuMkcLQaaKj47XRLL6nzt-cIMequoS9mhqoNFyDA289Elhapr2A-3EI-cPArWFW03_zvQPQc8rjkrCSq5XhP0q7nmqFI1A5mV2vRMYlo0mexYRHgZX5Vw'
```

**Response:**
Same as with the ```Device Data``` request, with data for a given day

# MQTT
>MQTT (..) is an ... publish-subscribe-based "lightweight" messaging protocol for use on top of the TCP/IP protocol. It is designed for connections with remote locations where a "small code footprint" is required or the network bandwidth is limited.  

source: Wikipedia [MQTT](https://en.wikipedia.org/wiki/MQTT)

## URL's / Endpoints
The specs for the MQTT broker are as the following:
* Host: ```tcp://mq.demo.ubirch.com:1883```
* Protocol: ```mqtt / tcp```

## Topics
For each device there is a topic available. The format for the topic is defined as the following:
```ubirch-demo/ubirch/devices/{{deviceID}}/processed```. Also the ```deviceID``` for the topic is the same a the ```deviceID``` for the REST API requests (e.g. ```a425081d-0737-4e0c-84ba-7137d57b4b10```).

## Authentification
User: ```telekom```  
Password: ```SmartPublicLife2017```

## Examples
For a quick start we recommend the [MQTTBox](http://workswithweb.com/mqttbox.html) app that can be downloaded for any platform from [here](http://workswithweb.com/html/mqttbox/downloads.html).
