//
//  YZInterceptionRule.h
//  YZBaseSDK
//
//  Created by jasper on 2026/4/12.
//  Copyright © 2026 Youzan. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 页面跳转白名单规则的匹配类型。
 */
typedef NS_ENUM(NSUInteger, YZInterceptionMatchType) {
    /** 精确匹配：目标 URL 与规则字符串完全相等（含 scheme/host/path/query）。 */
    YZInterceptionMatchTypeExact  = 0,
    /** 前缀匹配：目标 URL 的 host+path 以规则的 host+path 为前缀（scheme 不参与比较）。 */
    YZInterceptionMatchTypePrefix = 1,
};

@interface YZInterceptionRule : NSObject
/** 规则 URL 字符串。 */
@property (nonatomic, copy, readonly) NSString *url;

/** 匹配类型（精确 / 前缀）。 */
@property (nonatomic, assign, readonly) YZInterceptionMatchType matchType;

/**
 便捷构造方法。
 @param url       规则 URL 字符串
 @param matchType 匹配类型
 */
+ (instancetype)ruleWithURL:(NSString *)url matchType:(YZInterceptionMatchType)matchType;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
