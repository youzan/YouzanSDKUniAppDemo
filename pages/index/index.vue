<template>
	<view class="content">
		<!-- 列表区域 -->
		<view class="list-container">
			<!-- WebView组 -->
			<view class="group-title">WebView</view>
			<view 
				class="list-item" 
				v-for="(item, index) in webviewData" 
				:key="'webview-' + index"
				@click="handleItemClick(item)"
			>
				<view class="item-content">
					<view class="item-left">
						<text class="item-name">{{item.name}}</text>
						<text class="item-type">{{item.type}}</text>
					</view>
					<view class="item-right">
						<text class="arrow">></text>
					</view>
				</view>
			</view>
			
			<!-- 配置组 -->
			<view class="group-title">配置</view>
			<view 
				class="list-item" 
				v-for="(item, index) in configData" 
				:key="'config-' + index"
				@click="handleItemClick(item)"
			>
				<view class="item-content">
					<view class="item-left">
						<text class="item-name">{{item.name}}</text>
						<text class="item-type">{{item.type}}</text>
					</view>
					<view class="item-right">
						<text class="arrow">></text>
					</view>
				</view>
			</view>
		</view>
	</view>
</template>

<script>
	const systemInfo = uni.getSystemInfoSync();
	var yzModule = uni.requireNativePlugin("YouzanUniPlugin-YZUniModule")
	var globalEvent = uni.requireNativePlugin('globalEvent');
	export default {
		onLoad() {
			// 页面加载时自动初始化SDK
			this.initSDK()
			globalEvent.addEventListener('nativeLogEvent', function(e) {
				console.log("nativeLogEvent", e)
			});
		},
		data() {
			return {
				title: '功能列表',
				webUrl: 'https://shop96995477.m.youzan.com/v2/showcase/homepage?alias=LEDIZ83efK',
				// webUrl: 'https://shop42618405.youzan.com/v2/showcase/homepage?alias=1wFFbZ6566',
			//‘1', // ,
				// WebView组数据源
				webviewData: [
					{
						name: '不登录',
						type: 'unlogin',
						scheme: '/pages/second/second'
					},
					{
						name: '先登录',
						type: 'beforeLogin',
						scheme: '/pages/second/second'
					},
					{
						name: '后登录',
						type: 'afterLogin',
						scheme: '/pages/second/second'
					},
					{
						name: '拉起测试小程序',
						type: 'launchMiniProgram',
						scheme: ''
					}
				],
				// 配置组数据源
				configData: [
					{
						name: '手动初始化SDK1',
						type: 'initSDK',
						scheme: ''
					},
					{
						name: '自定义商店主页',
						type: 'customShopHome',
						scheme: ''
					},
					{
						name: '自定义页面',
						type: 'customPage',
						scheme: ''
					},
					{
						name: '复原页面',
						type: 'restorePage',
						scheme: ''
					},
					{
						name: '登录',
						type: 'login',
						scheme: ''
					},
					{
						name: '退出登录',
						type: 'logout',
						scheme: ''
					},
					{
						name: 'alipay跳转测试',
						type: 'alipayJumpTest',
						scheme: ''
					}
				]
			}
		},
		methods: {
			// 处理列表项点击
			handleItemClick(item) {
				// this.printLog('点击:'+item.name)
				switch(item.type) {
					case 'initSDK':
						this.initSDK()
						break
					case 'unlogin':
						this.handleNavigate(item.scheme, false)
						break
					case 'beforeLogin':
						this.handleNavigate(item.scheme, true)
						break
					case 'afterLogin':
						this.handleNavigate(item.scheme, false)
						break
					case 'launchMiniProgram':
						
						break
					case 'customShopHome':
						
						break
					case 'customPage':
						
						break
					case 'restorePage':
						this.restorePage()
						break
					case 'login':
						this.login()
						break
					case 'logout':
						this.logout()
						break
					case 'alipayJumpTest':
						
						break
					default:
						uni.showToast({
							title: '未知类型',
							icon: 'none'
						})
				}
			},
			
			// 处理页面跳转
			handleNavigate(url, needLogin) {
				if (!url) {
					uni.showToast({
						title: '跳转地址为空',
						icon: 'none'
					})
					return
				}
				if (needLogin) {
					yzModule.login({
							'user_id': '19988889999',
							'avatar': 'https://super-app-01.oss-cn-north-2-gov-1.aliyuncs.com/1375082/2021-02-09 10:08:43 lFeW.jpg',
							'extra': 'test',
							'nick_name': 'testName',
							'gender': 1,
						},
						(ret) => {
							// 刷新webview
							// 跳转下一个页面，需要把webUrl参数传过去
							uni.navigateTo({
								url: url + '?webUrl=' + this.webUrl,
								success: () => {
									// this.printLog('跳转成功')
								},
								fail: (err) => {
									// this.printLog('跳转失败')
									uni.showToast({
										title: '跳转失败',
										icon: 'none'
									})
								}
							})
						})
				} else {
					uni.navigateTo({
						url: url + '?webUrl=' + this.webUrl,
						success: () => {
							// this.printLog('跳转成功')
						},
						fail: (err) => {
							// this.printLog('跳转失败')
						}
					})
				}
			},

			// 复原页面
			restorePage() {
				this.webUrl = 'https://shop42618405.youzan.com/v2/showcase/homepage?alias=1wFFbZ6566'
				// this.printLog('复原页面成功')
			},
			
			// 初始化SDK
			initSDK() {
				const appkey = systemInfo.platform.toLowerCase() == "android" ?'76a4fbe055844b55be81114dddf6fd31': "1fb468088b70452fb7b7aed37e6a903b"
				const config = {
					'client_id': '1dab0042a6c6879f45', //1c3691de6f9aebc0d4',
					'app_key': appkey,
					'scheme': 'xxxx',
					"debug": true
				}
				
				// this.printLog("初始化配置:" + JSON.stringify(config))
				
				yzModule.setupSDK(config, (ret) => {
					uni.showToast({
						title: `初始化结果：${ret.success} message：${ret.message}`,
						icon: "none"
					})
				})
			},
			
			// 登录
			login() {
				yzModule.login({
						'user_id': '19988889999',
						'avatar': 'https://super-app-01.oss-cn-north-2-gov-1.aliyuncs.com/1375082/2021-02-09 10:08:43 lFeW.jpg',
						'extra': 'test',
						'nick_name': 'testName',
						'gender': 1,
					},
					(ret) => {
						// 刷新webview
						// this.printLog('登录成功')
					})
			},

			// 退出登录
			logout() {
				yzModule.logout((ret) => {
					// this.printLog('退出登录成功')
				})
			},
			
			// 打印日志
			printLog(log){
				if (yzModule?.nativeLog) {
					yzModule.nativeLog(log)
				} else {
					console.log(log)
				}
			}
		}
	}
</script>

<style>
	.content {
		display: flex;
		flex-direction: column;
		min-height: 100vh;
		background-color: #f5f5f5;
	}



	.list-container {
		flex: 1;
		padding: 20rpx;
	}

	.group-title {
		font-size: 28rpx;
		color: #666;
		font-weight: bold;
		margin: 30rpx 0 20rpx 10rpx;
		padding-left: 10rpx;
		border-left: 4rpx solid #ff6b00;
	}

	.list-item {
		background-color: white;
		margin-bottom: 20rpx;
		border-radius: 12rpx;
		overflow: hidden;
		box-shadow: 0 2rpx 8rpx rgba(0, 0, 0, 0.1);
	}

	.item-content {
		display: flex;
		align-items: center;
		justify-content: space-between;
		padding: 30rpx 40rpx;
	}

	.item-left {
		flex: 1;
		display: flex;
		flex-direction: column;
	}

	.item-name {
		font-size: 32rpx;
		color: #333;
		margin-bottom: 8rpx;
		font-weight: 500;
	}

	.item-type {
		font-size: 24rpx;
		color: #999;
		background-color: #f0f0f0;
		padding: 4rpx 12rpx;
		border-radius: 8rpx;
		align-self: flex-start;
	}

	.item-right {
		display: flex;
		align-items: center;
	}

	.arrow {
		font-size: 28rpx;
		color: #ccc;
	}
</style>