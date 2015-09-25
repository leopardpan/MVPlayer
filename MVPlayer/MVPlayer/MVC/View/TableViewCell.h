//
//  TableVewCell.h
//  MVPlayer
//
//  Created by 潘柏信 on 15/9/24.
//  Copyright (c) 2015年 leopard. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol CellDelegate <NSObject>
-(void)openMovieFile:(NSString *)file;
@end

@interface TableViewCell : UITableViewCell
@property (copy, nonatomic) NSString *url;
@property (nonatomic, weak) id<CellDelegate>delegate;
@end
