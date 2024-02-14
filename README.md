# MicroCryptoMonitor

MicroCryptoMonitor is a monitoring system designed for cryptocurrency mining farms, leveraging microcontroller technology along with InfluxDB and Grafana for advanced monitoring capabilities.

## Overview

Cryptocurrency mining farms require efficient monitoring systems to ensure optimal performance and resource utilization. MicroCryptoMonitor offers a comprehensive solution by integrating microcontrollers, InfluxDB, and Grafana to provide real-time monitoring of various parameters such as temperature, power consumption, and hash rates.

## Features

- **Microcontroller Integration**: Utilizes microcontrollers (e.g., ESP32) to collect real-time data from mining rigs.
- **InfluxDB Storage**: Stores collected data in InfluxDB, a time-series database, for efficient and scalable data management.
- **Grafana Dashboard**: Creates a user-friendly dashboard using Grafana to visualize and analyze key metrics of the mining farm.
- **Customizable Alerts**: Configurable alerts for abnormal conditions (e.g., high temperature, low hash rates) to ensure prompt action.
- **Scalable Architecture**: Docker-compose files provided for easy deployment and scalability of the monitoring system.

## Folder Structure

```
project-root/
│
├── ESP_Code/
│   ├── ESP_Code
│   └── ...
│
├── Docker/
│   ├── docker-compose.yml
│   └── .env
│   ├── grafana-provisioning/
│   │   ├── dashboard/
│   │   └── datasource/
│   └── ...
│
├── .gitignore
├── README.md
├── LICENSE
└── ...
```

## Installation

1. Clone the repository:

   ```
   git clone https://github.com/arya2004/MicroCryptoMonitor.git
   ```

2. Navigate to the `docker-compose` directory:

   ```
   cd MicroCryptoMonitor/docker-compose
   ```

3. Start the Docker containers:

   ```
   docker-compose up -d
   ```

4. Access Grafana dashboard at `http://localhost:3000` (default username: admin, password: admin).

## Usage

1. Flash ESP32 devices with provided Arduino code from `ESP32_Code` directory.
2. Configure InfluxDB data source in Grafana.
3. Import provided dashboard templates for visualizing mining farm data.
4. Customize alerts and thresholds as per your requirements.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
