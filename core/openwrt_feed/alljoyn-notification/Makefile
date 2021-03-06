# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
AJ_SERVICE:=notification
AJ_SERVICE_NAME:=Notification

include $(TOPDIR)/rules.mk

PKG_NAME:=alljoyn-$(AJ_SERVICE)
PKG_BASE_VERSION:=15.09
PKG_PATCHLEVEL:=.00dev
PKG_RELEASE:=1
PKG_MD5SUM:=
PKG_VERSION:=$(PKG_BASE_VERSION)$(PKG_PATCHLEVEL)
PKG_BUILD_DIR:=$(BUILD_DIR)/alljoyn-services-$(PKG_VERSION)-src
PKG_SOURCE:=alljoyn-services-$(PKG_VERSION)-src.tar.gz
#PKG_SOURCE_URL:=https://allseenalliance.org/releases/alljoyn/$(PKG_BASE_VERSION)/
PKG_SOURCE_URL:=https://build.allseenalliance.org/ci/job/master-source-extraction/lastSuccessfulBuild/artifact/depot/

# SCons supports parallel builds but does not support make's jobserver
PKG_BUILD_PARALLEL:=$(if $(CONFIG_PKG_BUILD_USE_JOBSERVER),0,1)

PKG_CONFIG_DEPENDS:= CONFIG_PACKAGE_$(PKG_NAME)-samples

include $(INCLUDE_DIR)/package.mk

ALLJOYN_BINDINGS:=cpp,
ALLJOYN_BUILD_SERVICES_SAMPLES:=off

define Package/$(PKG_NAME)
  TITLE:=AllJoyn $(AJ_SERVICE_NAME) service library
  SECTION:=net
  CATEGORY:=Network
  DEPENDS:=alljoyn \
	+alljoyn-about
  URL:=http://www.allseenalliance.org
  MAINTAINER:=AllSeen Alliance <allseen-core@lists.allseenalliance.org>
  MENU:=1
endef

define Package/$(PKG_NAME)/description
AllJoyn $(AJ_SERVICE_NAME) service library.
endef


define Package/$(PKG_NAME)-samples
$(call Package/$(PKG_NAME))
  TITLE+=- testing samples
  DEPENDS:=$(PKG_NAME) \
	+alljoyn-services_common
  MENU:=0
endef

define Package/$(PKG_NAME)-samples/description
Alljoyn $(AJ_SERVICE_NAME) service library samples.  (This is primarily for testing.
The contents of this package vary according which other alljoyn packages
are selected.)
endef


ifeq ($(CONFIG_DEBUG),y)
  ALLJOYN_BUILD_VARIANT:=debug
else
  ALLJOYN_BUILD_VARIANT:=release
endif


PKG_INSTALL_DIR:=$(PKG_BUILD_DIR)/services/base/$(AJ_SERVICE)/build/openwrt/openwrt/$(ALLJOYN_BUILD_VARIANT)/dist/$(AJ_SERVICE)

TARGET_CFLAGS+=-fPIC
TARGET_CPPFLAGS+=-fPIC

ifdef CONFIG_PACKAGE_$(PKG_NAME)-samples
  ifdef CONFIG_PACKAGE_alljoyn-about
    ALLJOYN_BUILD_SERVICES_SAMPLES:=on
  endif
endif

define Build/Configure/Default
# Override default to do nothing
endef

define Build/Compile
	scons -C $(PKG_BUILD_DIR)/services/base/$(AJ_SERVICE) \
		$(PKG_JOBS) \
		WS=off \
		CPU=openwrt \
		OS=openwrt \
		"BINDINGS=$(ALLJOYN_BINDINGS)" \
		"BUILD_SERVICES_SAMPLES=$(ALLJOYN_BUILD_SERVICES_SAMPLES)" \
		"VARIANT=$(ALLJOYN_BUILD_VARIANT)" \
		BR=off \
		BT=off \
		ICE=off \
		"TARGET_CC=$$(TARGET_CC)" \
		"TARGET_CXX=$$(TARGET_CXX)" \
		"TARGET_CFLAGS=$$(TARGET_CFLAGS)" \
		"TARGET_CPPFLAGS=$$(TARGET_CPPFLAGS)" \
		"TARGET_PATH=$$(TARGET_PATH)" \
		"TARGET_LINKFLAGS=$$(TARGET_LDFLAGS)" \
		"TARGET_LINK=$$(TARGET_CC)" \
		"TARGET_AR=$$(TARGET_AR)" \
		"TARGET_RANLIB=$$(TARGET_RANLIB)" \
		"STAGING_DIR=$$(STAGING_DIR)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/alljoyn/$(AJ_SERVICE)
	$(CP) $(PKG_INSTALL_DIR)/inc/alljoyn/$(AJ_SERVICE)/*.h $(1)/usr/include/alljoyn/$(AJ_SERVICE)
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/lib/liballjoyn_$(AJ_SERVICE).a $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/lib/liballjoyn_$(AJ_SERVICE).so $(1)/usr/lib/
endef


define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/lib/liballjoyn_$(AJ_SERVICE).so $(1)/usr/lib/
endef


define Package/$(PKG_NAME)-samples/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_INSTALL_DIR)/bin/* $(1)/usr/bin/
endef


$(eval $(call BuildPackage,$(PKG_NAME)))
$(eval $(call BuildPackage,$(PKG_NAME)-samples))

