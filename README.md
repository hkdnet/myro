# myro

Prometheus Exporter of Nature Remo

## Metrics

- nature_temperature{device_name="$name"}
- nature_humidity{device_name="$name"}
- nature_illumination{device_name="$name"}
- nature_movement{device_name="$name"}

## Environment Variables

- PORT
- NATURE_TOKEN

## Development

### Build

```
npm run build
```

### Watch

```
npm run watch
```

### Docker

```
docker build -t myro:latest .
```
