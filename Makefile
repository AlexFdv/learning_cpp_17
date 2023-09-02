.PHONY: clean All

All:
	@echo "----------Building project:[ Lesson_56_complex_objects_initialization - Debug ]----------"
	@cd "Lesson_56_complex_objects_initialization" && "$(MAKE)" -f  "Lesson_56_complex_objects_initialization.mk"
clean:
	@echo "----------Cleaning project:[ Lesson_56_complex_objects_initialization - Debug ]----------"
	@cd "Lesson_56_complex_objects_initialization" && "$(MAKE)" -f  "Lesson_56_complex_objects_initialization.mk" clean
