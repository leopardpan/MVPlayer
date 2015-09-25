//
//  VideoPlayerController.h
//  MVPlayer
//
//  Created by 潘柏信 on 15/9/24.
//  Copyright (c) 2015年 leopard. All rights reserved.
//

@import MediaPlayer;

@interface VideoPlayerController : MPMoviePlayerController

@property (nonatomic, copy)void(^dimissCompleteBlock)(void);
@property (nonatomic, assign) CGRect frame;

- (instancetype)initWithFrame:(CGRect)frame;
- (void)showInWindow;
- (void)dismiss;

@end