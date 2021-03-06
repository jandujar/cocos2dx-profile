/*
 Copyright (C) 2012-2014 Soomla Inc.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#include "CCProfileService.h"
#include "CCNdkBridge.h"
#include "CCDomainFactory.h"
#include "CCSoomlaProfile.h"
#include "CCProfileEventDispatcher.h"

using namespace cocos2d;

namespace soomla {

    USING_NS_CC;

    static CCProfileService *sInstance = NULL;

    CCProfileService *CCProfileService::getInstance() {
        if (!sInstance)
        {
            sInstance = new CCProfileService();
            sInstance->retain();
        }
        return sInstance;
    }

    void CCProfileService::initShared(__Dictionary *profileParams) {
        CCProfileService *profileService = CCProfileService::getInstance();
        if (!profileService->init(profileParams)) {
            exit(1);
        }
    }

    CCProfileService::CCProfileService() {
    }

    bool CCProfileService::init(__Dictionary *profileParams) {

        CCProfileEventDispatcher::getInstance();    // to get sure it's inited

        __Dictionary *params = __Dictionary::create();
        params->setObject(__String::create("CCProfileService::init"), "method");
        params->setObject(profileParams, "params");
        CCNdkBridge::callNative(params, nullptr);

        CCDomainFactory::getInstance()->registerCreator(CCProfileConsts::JSON_JSON_TYPE_USER_PROFILE,
                &CCUserProfile::createWithDictionary);

        return CCSoomlaProfile::getInstance()->init();
    }
}
