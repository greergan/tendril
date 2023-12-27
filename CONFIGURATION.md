| Required | Name | Data Type | Example | Default |
| -------- | ---- | --------- | ------- | ------- |
| YES | TENDRIL_NETWORK_LISTENERS  | **string**<br>array of comma separated members | [localhost:8500] | |
| NO  | TENDRIL_NETWORK_LISTENERS_BACK_PRESSURE  | **integer**<br>array of comma separated members corelating to the order of listeners | [100] | 100 |
| NO  | TENDRIL_NETWORK_LISTENERS_READ_TIMEOUT  | **milliseconds**<br>array of comma separated members corelating to the order of listeners | [1000] | 500 |
| NO  | TENDRIL_METRICS_SERVER_SERVE  | **boolean**<br/>when true, metrics server will start | true | false |
| NO  | TENDRIL_METRICS_SERVER_ADDRESS | **string**<br/>address and port used by metrics server | localhost:9000 | 127.0.0.1:9000 |
| YES | TENDRIL_KAFKA_BOOTSTRAP_SERVERS  | **string**<br/>comma separated list | localhost |  |