APP_VERSION := $(shell jq -r .version package.json)

.PHONY: build docker docker_push

build:
	npm run build-all

docker: build
	@echo "Building Docker image for version $(APP_VERSION)..."; \
	IMAGE_ID=$$(docker build --build-arg CACHEBUST=$$(date +%s) -q . | sed 's/sha256://'); \
	echo "Built image ID: $$IMAGE_ID"; \
	docker tag sha256:$$IMAGE_ID impleo/stserver:$(APP_VERSION); \
	docker tag sha256:$$IMAGE_ID impleo/stserver:latest; \
	echo "Tagged as impleo/stserver:$(APP_VERSION) and latest"

docker_push:
	@echo "Pushing Docker images for version $(APP_VERSION)..."; \
	docker push impleo/stserver:$(APP_VERSION); \
	docker push impleo/stserver:latest
