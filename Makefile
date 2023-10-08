.PHONY: clean All

All:
	@echo "----------Building project:[ Lesson_59_output_forwarding - Debug ]----------"
	@cd "Lesson_59_output_forwarding" && "$(MAKE)" -f  "Lesson_59_output_forwarding.mk"
clean:
	@echo "----------Cleaning project:[ Lesson_59_output_forwarding - Debug ]----------"
	@cd "Lesson_59_output_forwarding" && "$(MAKE)" -f  "Lesson_59_output_forwarding.mk" clean
