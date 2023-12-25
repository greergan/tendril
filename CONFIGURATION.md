| Required | Name | Data Type | Example | Default |
| -------- | ---- | --------- | ------- | ------- |
| YES | TENDRIL_NETWORK_TCP_LISTENERS  | **string**<br>array of comma separated members | [localhost:8500] | |
| NO  | TENDRIL_NETWORK_TCP_LISTENERS_BACK_PRESSURE  | **integer**<br>array of comma separated members corelating to the order of listeners | [100] | 100 |
| NO  | TENDRIL_NETWORK_TCP_LISTENERS_READ_TIMEOUT  | **milliseconds**<br>array of comma separated members corelating to the order of listeners | [1000] | 500 |
| NO  | TENDRIL_PROMETHEUS_EXPOSURE_ENDPOINT  | **string**<br/>exposes metrics to prometheus if configured | localhost:9000 |  |
| YES  | TENDRIL_KAFKA_BOOTSTRAP_SERVERS  | **string**<br/>comma separated list | localhost |  |