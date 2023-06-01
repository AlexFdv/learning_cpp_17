.PHONY: clean All

All:
	@echo "----------Building project:[ Lesson_46_Split_algo - Debug ]----------"
	@cd "Lesson_46_Split_algo" && "$(MAKE)" -f  "Lesson_46_Split_algo.mk"
clean:
	@echo "----------Cleaning project:[ Lesson_46_Split_algo - Debug ]----------"
	@cd "Lesson_46_Split_algo" && "$(MAKE)" -f  "Lesson_46_Split_algo.mk" clean
