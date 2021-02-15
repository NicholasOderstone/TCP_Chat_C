all:
	@make -C client
	@make -C server

install: all

uninstall:
	@make uninstall -C client
	@make uninstall -C server

clean:
	@make clean -C client
	@make clean -C server

reinstall: uninstall all
