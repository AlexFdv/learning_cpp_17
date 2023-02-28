.PHONY: clean All

All:
	@echo "----------Building project:[ Lesson_41_prefix_tree - Debug ]----------"
	@cd "Lesson_41_prefix_tree" && "$(MAKE)" -f  "Lesson_41_prefix_tree.mk"
clean:
	@echo "----------Cleaning project:[ Lesson_41_prefix_tree - Debug ]----------"
	@cd "Lesson_41_prefix_tree" && "$(MAKE)" -f  "Lesson_41_prefix_tree.mk" clean
