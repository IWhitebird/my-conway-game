make_my_game:
	cc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
build_my_game:
	cc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o my_conway_game
