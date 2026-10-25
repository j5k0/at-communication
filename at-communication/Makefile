include $(TOPDIR)/rules.mk

PKG_NAME:=at-communication
PKG_RELEASE:=1
PKG_VERSION:=1.0.0

include $(INCLUDE_DIR)/package.mk

define Package/at-communication
	CATEGORY:=Base system
	TITLE:=AT Communication with RUTX11
endef

define Package/at-communication/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/at-communication $(1)/usr/bin
endef

$(eval $(call BuildPackage,at-communication))