MANDATORY = cub3D
BONUS = cub3D_bonus

all : $(MANDATORY)

$(MANDATORY) :
	@make -s -C ./mandatory
	@cp mandatory/Cub3D ./cub3D

bonus : $(BONUS)

$(BONUS) :
	@make -s -C ./bonus
	@cp bonus/Cub3D ./cub3D_bonus

clean :
	@echo "MANDATORY.."
	@make -s -C ./mandatory clean
	@echo "BONUS.."
	@make -s -C ./bonus clean

fclean : clean
	@echo "MANDATORY.."
	@make -s -C ./mandatory fclean
	@echo "BONUS.."
	@make -s -C ./bonus fclean
	@rm -fr $(MANDATORY) $(BONUS)

re : fclean all

.PHONY: all clean fclean re