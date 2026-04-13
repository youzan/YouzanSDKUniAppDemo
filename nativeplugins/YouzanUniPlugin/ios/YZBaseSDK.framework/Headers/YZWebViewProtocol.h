//
//  YZWebViewProtocol.h
//  YZWebViewFramework
//
//  Created by Pan on 2017/11/14.
//  Copyright © 2017年 Youzan. All rights reserved.
//

#ifndef YZWebViewProtocol_h
#define YZWebViewProtocol_h

#import <UIKit/UIKit.h>
#import <JavaScriptCore/JavaScriptCore.h>
#import <WebKit/WebKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol YZWebView;

@class YZInterceptionRule;

@protocol YZWebViewDelegate <NSObject>

@optional
- (BOOL)webView:(id<YZWebView>)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(WKNavigationType)navigationType;

/**
 容器级页面跳转白名单拦截回调。
 当目标 URL 命中通过 setNavigationInterceptionURLRules: 注册的白名单规则时触发。
 仅在所有原有拦截逻辑放行后、且命中白名单时才回调；SDK 不继续执行默认跳转。
 */
- (void)webView:(id<YZWebView>)webView didInterceptNavigationWithRequest:(NSURLRequest *)request navigationType:(WKNavigationType)navigationType;

- (void)webViewDidStartLoad:(id<YZWebView>)webView;
- (void)webViewDidFinishLoad:(id<YZWebView>)webView;
- (void)webView:(id<YZWebView>)webView didFailLoadWithError:(NSError *)error;
- (void)webView:(id<YZWebView>)webView didFailProvisionalNavigation:(WKNavigation *)navigation withError:(NSError *)error;
- (void)webViewWebContentProcessDidTerminate:(id<YZWebView>)webView;

@end

@protocol YZWebViewUIDelegate <NSObject>

@optional

- (void)webViewDidChangeContentOffset:(id<YZWebView>)webView fromValue:(CGPoint)fromValue toValue:(CGPoint)toValue;
- (void)webViewDidChangeContentSize:(id<YZWebView>)webView fromValue:(CGSize)fromValue toValue:(CGSize)toValue;

@end
@protocol YZWebView <NSObject>

/**
 代理对象，实现它来监听 YZNotice, 在得到对应通知的时候，做对应的操作。
 */
@property (nonatomic, weak, nullable) id<YZWebViewDelegate> delegate;
@property (nonatomic, weak, nullable) id<YZWebViewUIDelegate> uiDelegate;

@property (nonatomic, strong, readonly) UIScrollView *scrollView;
@property (nonatomic, strong, readonly, nullable) NSURLRequest *originRequest;    //webview页面初始请求
@property (nonatomic, strong, readonly, nullable) NSURLRequest *currentRequest;
@property (nonatomic, strong, readonly, nullable) NSURL *URL;
@property (nonatomic, strong, readonly, nullable) JSContext *jsContext;
@property (nonatomic, assign, readonly,getter=isLoading) BOOL loading;
@property (nonatomic, assign, readonly) BOOL canGoBack;
@property (nonatomic, assign, readonly) BOOL canGoForward;
@property (nonatomic, assign, readonly) BOOL isDragging;    // 是否在拖拽
@property (nonatomic, assign) BOOL scalesPageToFit;

@property (nonatomic, readonly) double estimatedProgress;

/**
 设置页面跳转白名单拦截规则。
 每条规则包含 URL 字符串与匹配类型（精确 / 前缀），由业务方显式指定。
 传入 nil 或空数组时清空规则，不拦截任何跳转。
 @param rules YZInterceptionRule 规则数组
 */
- (void)setNavigationInterceptionRules:(nullable NSArray<YZInterceptionRule *> *)rules;

/**
 容器级 loading 开关。
 - 显式赋值 NO（默认）：遵从 YZConfig.disableDefaultLoading 全局配置。
 - 显式赋值 YES：该容器关闭 SDK loading，不论全局配置。
 */
@property (nonatomic, assign) BOOL disableLoading;

- (void)loadRequest:(NSURLRequest *)request;
- (void)loadHTMLString:(NSString *)string baseURL:(nullable NSURL *)baseURL;
- (void)loadData:(NSData *)data
MIMEType:(NSString *)MIMEType
textEncodingName:(NSString *)textEncodingName
baseURL:(NSURL *)baseURL;

- (void)reload;
- (void)reloadFromOrigin;
- (void)stopLoading;

- (void)goBack;
- (void)goForward;
- (void)gobackWithStep:(NSInteger)step;

- (NSInteger)countOfHistory;
- (NSArray<WKBackForwardListItem *> *)backList;

- (NSString *)stringByEvaluatingJavaScriptFromString:(NSString *)javaScriptString;
- (void)evaluateJavaScript:(NSString *)javaScriptString
         completionHandler:(void (^ _Nullable)(id _Nullable response, NSError *_Nullable error))completionHandler;

- (void)addScriptMessageHandler:(id <WKScriptMessageHandler>)scriptMessageHandler name:(NSString *)name;
- (void)removeScriptMessageHandlerForName:(NSString *)name;

@end

NS_ASSUME_NONNULL_END

#endif /* YZWebViewProtocol_h */

