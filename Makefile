APP_TITLE := Friday Night Funkin'
APP_AUTHOR := NicktasticToons
APP_SHORT_DESC := Short Description
APP_LONG_DESC := Long Description
APP_VERSION := 0.0.0
TARGET := funkin

.PHONY: all engine game clean run package

all: engine game

engine:
	@$(MAKE) -C engine

game:
	@$(MAKE) -C funkin

clean:
	@$(MAKE) -C funkin clean || true
	@$(MAKE) -C engine clean || true
	@rm -rf out

run: game
	open -a Dolphin funkin/build/$(TARGET).dol

package: game
	@echo Packaging...
	@rm -rf package out
	@mkdir -p package/apps/$(TARGET)
	@cp funkin/build/$(TARGET).dol package/apps/$(TARGET)/boot.dol
	@echo "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" > package/apps/$(TARGET)/meta.xml
	@echo "<app version=\"$(APP_VERSION)\">" >> package/apps/$(TARGET)/meta.xml
	@echo "\t<name>$(APP_TITLE)</name>" >> package/apps/$(TARGET)/meta.xml
	@echo "\t<coder>$(APP_AUTHOR)</coder>" >> package/apps/$(TARGET)/meta.xml
	@echo "\t<version>$(APP_VERSION)</version>" >> package/apps/$(TARGET)/meta.xml
	@echo "\t<short_description>$(APP_SHORT_DESC)</short_description>" >> package/apps/$(TARGET)/meta.xml
	@echo "\t<long_description>$(APP_LONG_DESC)</long_description>" >> package/apps/$(TARGET)/meta.xml
	@echo "</app>" >> package/apps/$(TARGET)/meta.xml
	@if [ -f gfx/wii/icon.png ]; then cp gfx/wii/icon.png package/apps/$(TARGET)/icon.png; fi
	@mkdir -p out
	@cd package && zip -r ../out/$(TARGET).zip apps/
	@rm -rf package
	@echo Package created: out/$(TARGET).zip

