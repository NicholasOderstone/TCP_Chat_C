all:
	@make -C client
	@make -C server

uninstall: clean
	@make uninstall -C client
	@make uninstall -C server

clean:
	@make clean -C client
	@make clean -C client

reinstall: uninstall all
