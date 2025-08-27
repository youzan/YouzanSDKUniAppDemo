# 有赞UniApp插件接入文档
## 项目概述
本项目是有赞SDK在UniApp中的集成示例，提供了完整的电商WebView功能，包括用户登录、商品浏览、购物车、支付等功能。
##  插件初始化
### 引入插件模块// 引入有赞插件模块
```
var yzModule = uni.requireNativePlugin("YouzanUniPlugin-YZUniModule")
```

### SDK 初始化

// 初始化SDK
```
initSDK() {
  const systemInfo = uni.getSystemInfoSync();
  // Android和iOS使用不同的app_key
  const appkey = systemInfo.platform.toLowerCase() == "android" 
    ? '76a4fbe055844b55be81114dddf6fd31' 
    : "your_ios_app_key"
  
  const config = {
    'client_id': '1c3691de6f9aebc0d4',
    'app_key': appkey,
    'scheme': 'your_custom_scheme',
    "debug": false
  }
  
  yzModule.setupSDK(config, (ret) => {
    uni.showToast({
      title: `初始化结果：${ret.success} message：${ret.message}`,
      icon: "none"
    })
  })
}
```

### 组件使用
```
<template>
  <view class="webview-container">
    <yz-webview
      class="webview" 
      ref='yzwebview'
      :url="webUrl"
      @receivedTitle="onReceivedTitle"
      @jsBridgeEvent="onJsBridgeEvent"
      @webViewFinishLoad="onWebViewFinishLoad" 
      @webViewStartLoad="onWebViewStartLoad"
      @webViewLoadError="onWebViewLoadError" 
      @nativeLogEvent="onNativeLogEvent">
    </yz-webview>
  </view>
</template>
```
