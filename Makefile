.PHONY: clean All

All:
	@echo "----------Building project:[ Lesson_47_algos_based_on_gather - Debug ]----------"
	@cd "Lesson_47_algos_based_on_gather" && "$(MAKE)" -f  "Lesson_47_algos_based_on_gather.mk"
clean:
	@echo "----------Cleaning project:[ Lesson_47_algos_based_on_gather - Debug ]----------"
	@cd "Lesson_47_algos_based_on_gather" && "$(MAKE)" -f  "Lesson_47_algos_based_on_gather.mk" clean
