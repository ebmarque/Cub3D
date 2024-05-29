MANDATORY = Cub3D
BONUS = Cub3D_Bonus

all : $(MANDATORY)

$(MANDATORY) :
	@make -s -C ./mandatory
	@cp mandatory/Cub3D ./Cub3D

bonus : $(BONUS)

$(BONUS) :
	@make -s -C ./bonus
	@cp bonus/Cub3D ./Cub3D_Bonus

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