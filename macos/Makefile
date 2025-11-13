.DEFAULT_GOAL := Dockerfile
prep:
	colima start docker
Dockerfile: prep
	docker build -t kursovaya_rabota .
run: 
	docker run -it --mount type=bind,src=../make,dst=/home/user/ --rm -e DISPLAY=host.docker.internal:0 \
	--mount type=bind,src=/tmp/.X11-unix,dst=/tmp/.X11-unix kursovaya_rabota 
