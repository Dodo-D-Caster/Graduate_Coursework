//
//  GameScene.swift
//  PokemonJump
//
//  Created by Mac on 2020/12/8.
//  Copyright © 2020年 Mac. All rights reserved.
//

import SpriteKit
//图层
enum fbLayer: CGFloat {
    case backGround  //背景
    case barrie //障碍物
    case foreGround  //前景
    case gameUser    //游戏角色
    case UI //UI
}
//物理层
struct physicsLayer {
    static let null:UInt32 =        0
    static let gameUser:UInt32 =        0b1  //1
    static let barrier:UInt32 =        0b10   //2
    static let floor:UInt32 =        0b100  //4
}
//游戏状态
enum gameState {
    case mainMenu  //主菜单
    case course   //教程
    case playing  //游戏中
    case fall  //跌落
    case showScore  //显示分数
    case gameOver   //结束
}
//MARK:主要逻辑
class GameScene: SKScene {
    
    var jumpCount = 0 //跳跃次数，最大二段跳
    let foreGroundCount = 2 //前景地面数量
    let foreGroundMoveSpeed = -150.0 //地面移动速度
    let gravity:CGFloat = -1500.0  //重力 每一秒下降1500像素
    let flyUpSpeed = 800.0  //嘎啦嘎啦跳起速度
    let barrierMin:CGFloat = 0.1 //障碍物最小乘数
    let barrierMax:CGFloat = 0.6 //障碍物最大乘数
    let gap:CGFloat = 3.5 //缺口乘数
    let firstMakeBarrierInterval:TimeInterval = 3 //首次生成障碍延迟
    let rebirthMakeBarrierInterval:TimeInterval = 1.75 //每次重生障碍延迟
    
    
    let topWhite:CGFloat = 20.0 //顶部留白
    let fontFamily = "AmericanTypewriter-Bold" //字体  Zapfino
    var scoreLabel = SKLabelNode()  //得分标签
    var currentScore = 0 //当前分数
    let animationDelay = 0.3 //动画延迟
    let userframeNumber = 4  //角色动画总帧数
    
    var birdspeed = CGPoint.zero   //速度
    var crashFloor = false   //碰撞了地面
    var crashBarrier = false  //碰撞了障碍物
    var currentGameState: gameState = .playing  //当前游戏状态
    
    let gameNode = SKNode()   //游戏世界
    var regionalSart:CGFloat = 0 //游戏区域起始点
    var regionalHeight:CGFloat = 0    //游戏区域高度
    let gameUser = SKSpriteNode.init(imageNamed: "Bird0") //游戏主角
    var lastUpdateTime : TimeInterval = 0 //上一次更新时间
    var dt:TimeInterval = 0
    
    override func didMove(to view: SKView) {
        
        //关掉重力
        physicsWorld.gravity = CGVector.init(dx: 0, dy: 0)
        //设置代理
        physicsWorld.contactDelegate  = self
        addChild(gameNode)
        switchMainMenu()  //切换主菜单

    }
    
       override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        guard let touch = touches.first else {
            return   //只取第一次点击
        }
        let touchCoordinate = touch.location(in: self) //点击位置
        switch currentGameState {
        case .mainMenu:
            if(touchCoordinate.x <= size.width*0.75 && touchCoordinate.x >= size.width*0.25) {
                    switchCourseState()  //切换至教程状态
            }
            break
        case .course:
            switchPlayingState()
            break
        case .playing:
            birdFly() //跳一下
            break
        case .fall:
            break
        case .showScore:
            break
        case .gameOver:
            newGame()  //切换至新游戏
            break
            
        }
    }

    /**
     * 嘎啦嘎啦跳一次
     */
    func birdFly(){
        jumpCount = jumpCount + 1
        if(jumpCount > 2)
        {
            return
        }
        
        birdspeed = CGPoint.init(x: 0, y: flyUpSpeed)
        
    }
    /**
     * 每一帧都会调用更新
     */
    override func update(_ currentTime: TimeInterval) {

        
        if (lastUpdateTime > 0){
            dt = currentTime  - lastUpdateTime
        } else {
            dt = 0
        }
        lastUpdateTime = currentTime
        
        switch currentGameState {
        case .mainMenu:
            break
        case .course:
            break
        case .playing:
            updateGameUser()  //更新主角
            updateForeGround()  //更新前景
            crashBarrierDetection() //撞击障碍物检查
            crashFloorDetection()  //撞击地面检查
            updateScore() //更新得分
            
            break
        case .fall:
            updateGameUser()  //更新主角
            crashFloorDetection()  //撞击地面检查
            break
        case .showScore:
            break
        case .gameOver:
            break
            
        }
        
        
    }
    /**
     * 更新游戏主角(嘎啦嘎啦)
     */
    func updateGameUser(){
        let acceleratedSpeed = CGPoint.init(x: 0, y: gravity)  //加速度 上下移动
        birdspeed = birdspeed + acceleratedSpeed * CGFloat(dt)
        gameUser.position = gameUser.position + birdspeed * CGFloat(dt)
        
        //检测到撞击地面就让嘎啦嘎啦鸟停在地面
        if (gameUser.position.y - gameUser.size.height/2 < regionalSart){
            gameUser.position = CGPoint.init(x: gameUser.position.x, y: regionalSart + gameUser.size.height / 2)
        }
        //跳太高就让其留在顶部
        if(gameUser.position.y > size.height){
            gameUser.position = CGPoint.init(x: gameUser.position.x, y:  size.height)
        }
    }
    /**
     * 更新前景
     */
    func updateForeGround(){
        gameNode.enumerateChildNodes(withName: "foreGround") { (matchingUnit, _) in
            if let foreGround = matchingUnit as? SKSpriteNode {
                let foreGroundMoveSpeed = CGPoint.init(x: self.foreGroundMoveSpeed, y: 0)
                foreGround.position += foreGroundMoveSpeed * CGFloat(self.dt)
                
                if(foreGround.position.x < -foreGround.size.width){
                    foreGround.position += CGPoint.init(x: foreGround.size.width * CGFloat(self.foreGroundCount), y: 0)
                }
                
            }
        }
    }
    /**
     * 撞击障碍物检查
     */
    func crashBarrierDetection(){
        if crashBarrier {
            crashBarrier = false
            switchFallState() //切换到跌落状态
            gameUser.position = CGPoint.init(x: gameUser.position.x, y:regionalSart + gameUser.size.width/2 ) //嘎啦嘎啦的位置
            switchShowScore()   //切换到显示分数
        }
    }
    /**
     * 撞击地面检查
     */
    func crashFloorDetection(){
        if crashFloor {
            crashFloor = false
            jumpCount = 0
        }
    }
    
    /**
     * 更新得分
     */
    func updateScore(){
        gameNode.enumerateChildNodes(withName: "topBarrier") { (matchingUnit, _) in
            if let barrier = matchingUnit as? SKSpriteNode {
                if let  passed = barrier.userData?["passed"] as? NSNumber {
                    if passed.boolValue {
                        return  //已经计算过一次得分
                    }
                }
                if (self.gameUser.position.x > barrier.position.x + barrier.size.width/2){
                    //嘎啦嘎啦已经完全通过障碍物
                    self.currentScore = self.currentScore + 1
                    self.scoreLabel.text = "\(self.currentScore)"
                    barrier.userData?["passed"]  = NSNumber.init(value: true)
                }
                
            }
            
        }
        
    }
 
    /**
     * 取值最高分数
     */
    func highestScore() -> Int {
         return UserDefaults.standard.integer(forKey: "highestScore")  //取到最高分
    }
    /**
     * 本地化最高分数
     */
    func settingHighestScore(highestScore:Int){
         UserDefaults.standard.set(highestScore, forKey: "highestScore")
        UserDefaults.standard.synchronize()
    }
    
}

//MARK:生成UI
extension GameScene{
    /**
     * 设置背景
     */
    func settingUpBackGround (){
        let backGround = SKSpriteNode.init(imageNamed: "Background")
        backGround.anchorPoint = CGPoint.init(x: 0.5, y: 1.0)  //锚点
        backGround.position  = CGPoint.init(x: size.width/2, y: size.height) //位置
        backGround.zPosition = fbLayer.backGround.rawValue //z轴的原始值
        gameNode.addChild(backGround) //添加背景到游戏世界上面
        
        //计算
        regionalSart = size.height - backGround.size.height
        regionalHeight = backGround.size.height
        
        //地面的碰撞参数
        let leftBottom = CGPoint.init(x: 0, y: regionalSart)
        let rightBottom = CGPoint.init(x: size.width, y: regionalSart)
        
        self.physicsBody = SKPhysicsBody.init(edgeFrom: leftBottom, to: rightBottom)
        self.physicsBody?.categoryBitMask = physicsLayer.floor //类别源码
        self.physicsBody?.contactTestBitMask = 0   //关闭系统的碰撞处理
        self.physicsBody?.contactTestBitMask = physicsLayer.gameUser  //打开碰撞检测
        
    }
    /**
     * 设置前景
     */
    func settingForeGround(){
        for i in 0..<foreGroundCount {
            let foreGround = SKSpriteNode.init(imageNamed: "Ground")
            foreGround.anchorPoint = CGPoint.init(x: 0, y: 1.0) //锚点
            foreGround.position = CGPoint.init(x: CGFloat(i) * foreGround.size.width, y: regionalSart)//位置
            foreGround.zPosition = fbLayer.foreGround.rawValue//z轴的原始值
            foreGround.name = "foreGround" //方便查找到foreGround
            gameNode.addChild(foreGround)//添加前景到游戏世界上面
        }
        
        
    }
    /**
     * 设置游戏主角
     */
    func settingGameUser(){
        gameUser.position = CGPoint.init(x: size.width * 0.2, y:regionalSart)//位置
        gameUser.zPosition = fbLayer.foreGround.rawValue//z轴的原始值
        
        //碰撞体积
        let offsetX = gameUser.size.width * gameUser.anchorPoint.x
        let offsetY = gameUser.size.height * gameUser.anchorPoint.y
        
        let path = CGMutablePath()
        
        path.move(to: CGPoint(x:  2 - offsetX, y: 14 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  15 - offsetX, y: 23 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  31 - offsetX, y: 29 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  38 - offsetX, y: 19 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  38 - offsetX, y: 9 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  34 - offsetX, y: 4 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  24 - offsetX,  y: 3 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  20 - offsetX,  y: 1 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  7 - offsetX,  y: 0 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  5 - offsetX,  y: 1 - offsetY), transform: CGAffineTransform.identity)
        path.closeSubpath()
        gameUser.physicsBody = SKPhysicsBody(polygonFrom: path)
        gameUser.physicsBody?.categoryBitMask = physicsLayer.gameUser //类别源码
        gameUser.physicsBody?.collisionBitMask = 0  //关闭系统的碰撞处理
        gameUser.physicsBody?.contactTestBitMask = physicsLayer.barrier | physicsLayer.floor     //打开碰撞检测
        
        
        gameNode.addChild(gameUser)//添加前景到游戏世界上面
    }

    /**
     * 设置得分标签
     */
    func settingScoreLabel(){
        scoreLabel = SKLabelNode.init(fontNamed: fontFamily) //字体
        scoreLabel.fontColor = SKColor.init(red: 101.0/255.0, green: 71.0/255.0, blue: 73.0/255.0, alpha: 1.0) //字体颜色
        scoreLabel.position = CGPoint.init(x: size.width/2, y: size.height - topWhite) //位置
        scoreLabel.verticalAlignmentMode = .top //垂直方向的对齐方式
        scoreLabel.text = "0"
        scoreLabel.zPosition = fbLayer.UI.rawValue //设置z轴位置
        gameNode.addChild(scoreLabel)
        
    }

    /**
     * 设置主菜单
     */
    func settingMainMenu(){
        //logo
        let logo = SKSpriteNode(imageNamed: "Logo")
        logo.position = CGPoint(x: size.width/2, y: size.height * 0.8)
        logo.name = "MainMenu"
        logo.zPosition = fbLayer.UI.rawValue
        gameNode.addChild(logo)
        
        // 开始游戏按钮
        
        let startGameBtn = SKSpriteNode(imageNamed: "Button")
        startGameBtn.position = CGPoint(x: size.width * 0.5, y: size.height * 0.25)
        startGameBtn.name = "MainMenu"
        startGameBtn.zPosition = fbLayer.UI.rawValue
        gameNode.addChild(startGameBtn)
        
        let playBtn = SKSpriteNode(imageNamed: "Play")
        playBtn.position = CGPoint.zero
        startGameBtn.addChild(playBtn)
    }
    /**
     * 设置教程
     */
    func  settingCourse(){
        //教程
        let course = SKSpriteNode.init(imageNamed: "Tutorial")
        course.position = CGPoint.init(x: size.width * 0.5, y: regionalHeight * 0.4 + regionalSart) //位置
        course.name = "course" //标示
        course.zPosition = fbLayer.UI.rawValue //图层
        gameNode.addChild(course)  //添加到游戏世界
        
        //准备
        let  prepare = SKSpriteNode.init(imageNamed: "ready")
        prepare.position = CGPoint.init(x: size.width * 0.5, y: regionalHeight * 0.7 + regionalSart)//位置
        prepare.name  = "course"//标示
        prepare.zPosition = fbLayer.UI.rawValue//图层
        gameNode.addChild(prepare) //添加到游戏世界
        
        let topMove = SKAction.moveBy(x: 0, y: 50, duration: 0.4)
        topMove.timingMode = .easeInEaseOut
        let botttomMove = topMove.reversed()
        
        gameUser.run(SKAction.repeatForever(SKAction.sequence([
            topMove,botttomMove
            ])), withKey: "fly")
        
        var userImgAry: Array<SKTexture> = []
        
        for i in 0..<userframeNumber {
            userImgAry.append(SKTexture(imageNamed: "Bird\(i)"))
        }
        
        for i in stride(from:  (userframeNumber-1), through: 0, by: -1){
            userImgAry.append(SKTexture(imageNamed: "Bird\(i)"))
        }
        
        let wingAnimation = SKAction.animate(with: userImgAry, timePerFrame: 0.07)
        gameUser.run(SKAction.repeatForever(wingAnimation))
        
    }
    /**
     * 设置计分板
     */
    func settingScoreCard(){
        if(currentScore > highestScore()){   //如果当前分数大于最高分则记录
            settingHighestScore(highestScore: currentScore)
        }
        
        //        计分板
        let scoreCard = SKSpriteNode.init(imageNamed: "ScoreCard")
        scoreCard.position = CGPoint.init(x: size.width/2, y: size.height/2)  //位置
        scoreCard.zPosition = fbLayer.UI.rawValue  //z轴位置(图层)
        gameNode.addChild(scoreCard)  //添加到游戏世界
        
        //        当前分数标签
        let currentScoreLabel = SKLabelNode.init(fontNamed: fontFamily) //字体
        currentScoreLabel.fontColor = SKColor.init(red: 101.0/255.0, green: 71.0/255.0, blue: 73.0/255.0, alpha: 1.0)//颜色
        currentScoreLabel.position = CGPoint.init(x: -scoreCard.size.width / 4, y: -scoreCard.size.height / 3) //位置
        currentScoreLabel.text = "\(currentScore)"
        currentScoreLabel.zPosition = fbLayer.UI.rawValue //z轴位置(图层)
        scoreCard.addChild(currentScoreLabel)  //添加到游戏世界
        
        //        最高分数标签
        let highestScoreLabel = SKLabelNode.init(fontNamed: fontFamily) //字体
        highestScoreLabel.fontColor = SKColor.init(red: 101.0/255.0, green: 71.0/255.0, blue: 73.0/255.0, alpha: 1.0)//颜色
        highestScoreLabel.position = CGPoint.init(x: scoreCard.size.width / 4, y: -scoreCard.size.height / 3) //位置
        highestScoreLabel.text = "\(highestScore())"
        highestScoreLabel.zPosition = fbLayer.UI.rawValue //z轴位置(图层)
        scoreCard.addChild(highestScoreLabel)  //添加到游戏世界
        
        //        gameOver
        let gameOverLabel = SKSpriteNode.init(imageNamed: "GameOver")
        gameOverLabel.position = CGPoint.init(x: size.width/2, y: size.height/2 + scoreCard.size.height/2 + topWhite + gameOverLabel.size.height/2)//位置
        gameOverLabel.zPosition = fbLayer.UI.rawValue //z轴位置(图层)
        gameNode.addChild(gameOverLabel) //添加到游戏世界
        
        //        OK按钮
        let okBtn = SKSpriteNode.init(imageNamed: "Button")
        okBtn.position = CGPoint.init(x: size.width/2, y: size.height/2 - scoreCard.size.height/2 - okBtn.size.height/2)//位置
        okBtn.zPosition = fbLayer.UI.rawValue//z轴位置(图层)
        gameNode.addChild(okBtn)//添加到游戏世界
        
        //        OK按钮上面的文字
        let ok = SKSpriteNode.init(imageNamed: "OK")
        ok.position = CGPoint.zero
        ok.zPosition = fbLayer.UI.rawValue
        okBtn.addChild(ok) //ok文字添加到OK按钮之上
        

        //动画特效gameOver
        gameOverLabel.setScale(0)  //先缩0
        gameOverLabel.alpha = 0
        let animationQueue = SKAction.group([  //动画组
            SKAction.fadeIn(withDuration: animationDelay),
            SKAction.scale(to: 1.0, duration: animationDelay)
            ])
        animationQueue.timingMode = .easeInEaseOut  //动画函数
        gameOverLabel.run(SKAction.sequence([
            SKAction.wait(forDuration: animationDelay),  //延迟
            animationQueue
            ]))
        //动画特效计分板
        scoreCard.position = CGPoint.init(x: size.width / 2, y: -scoreCard.size.height/2) //位置
        let moveAnimation = SKAction.move(to: CGPoint.init(x: size.width / 2, y: size.height / 2), duration: animationDelay) //向上移动动画
        moveAnimation.timingMode = .easeInEaseOut  //动画函数
        scoreCard.run(SKAction.sequence([
            SKAction.wait(forDuration: animationDelay * 2),
            moveAnimation
            ]))
        //OK按钮特效
        okBtn.alpha = 0
        let btnAnimation = SKAction.sequence([
            SKAction.wait(forDuration: animationDelay * 3),
            SKAction.fadeIn(withDuration: animationDelay)
            ])
        okBtn.run(btnAnimation)
        //动画
        let songAnimation = SKAction.sequence([
            SKAction.run(switchGameOverState)  //切换至游戏结束状态
            ])
        run(songAnimation)
    }

    /**
     * 创建障碍物
     */
    func makeBarrier(imgName:String) -> SKSpriteNode{
        let barrie = SKSpriteNode.init(imageNamed: imgName)  //障碍物
        barrie.zPosition = fbLayer.barrie.rawValue //z轴的原始值
        
        barrie.userData = NSMutableDictionary() //初始化数据
        
        
        let offsetX = barrie.size.width * barrie.anchorPoint.x
        let offsetY = barrie.size.height * barrie.anchorPoint.y
        
        let path = CGMutablePath()
        
        path.move(to: CGPoint(x:  3 - offsetX, y: 1 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  3 - offsetX, y: 27 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  2 - offsetX, y: 70 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  5 - offsetX, y: 216 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  6 - offsetX, y: 311 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  49 - offsetX, y: 312 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  48 - offsetX,  y: 185 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  47 - offsetX,  y: 85 - offsetY), transform: CGAffineTransform.identity)
        path.addLine(to: CGPoint(x:  49 - offsetX,  y: 1 - offsetY), transform: CGAffineTransform.identity)
        
        path.closeSubpath()
        barrie.physicsBody = SKPhysicsBody(polygonFrom: path)
        barrie.physicsBody?.collisionBitMask = 0 //关闭系统的碰撞处理
        barrie.physicsBody?.categoryBitMask = physicsLayer.barrier//类别源码
        barrie.physicsBody?.contactTestBitMask = physicsLayer.gameUser  //打开碰撞检测
        
        return barrie
    }
    /**
     * 生成障碍
     */
    func outPutBarrier(){
        //底部障碍
        let bottomBarrie = makeBarrier(imgName: "CactusBottom")
        bottomBarrie.name = "bottomBarrie"
        let startX = size.width + bottomBarrie.size.width/2
        let minY =  (regionalSart - bottomBarrie.size.height/2) + regionalHeight * barrierMin
        let maxY = (regionalSart - bottomBarrie.size.height/2) + regionalHeight * barrierMax
        bottomBarrie.position = CGPoint.init(x: startX, y: CGFloat.random(min: minY, max: maxY))
        gameNode.addChild(bottomBarrie)
        //顶部障碍
        let topBarrier = makeBarrier(imgName: "CactusTop")
        topBarrier.name = "topBarrier"
        topBarrier.zRotation = CGFloat(180).degreesToRadians()
        topBarrier.position = CGPoint.init(x: startX, y: 0)
        gameNode.addChild(topBarrier)
        //移动参数
        let moveX = -(size.width + bottomBarrie.size.width)  //X轴移动距离
        let moveTime = moveX / CGFloat(foreGroundMoveSpeed)   //移动持续时间
        let moveQueue = SKAction.sequence([
            SKAction.moveBy(x: moveX, y: 0, duration: TimeInterval(moveTime)),
            SKAction.removeFromParent()
            ])  //移动队列
        topBarrier.run(moveQueue)
        bottomBarrie.run(moveQueue)
    }
    /**
     * 无限重生障碍
     */
    
    func infiniteMakeBarrier(){
        let firstInterval = SKAction.wait(forDuration: firstMakeBarrierInterval) //首次延迟
        let rebirthBarrie = SKAction.run (outPutBarrier)  //重生障碍
        let rebirthInterval = SKAction.wait(forDuration: firstMakeBarrierInterval) //每次重生间隔
        let rebirthQueue = SKAction.sequence([rebirthBarrie,rebirthInterval])  //重生队列
        let infiniteRebirth = SKAction.repeatForever(rebirthQueue)  //无限重生
        let totalQueue = SKAction.sequence([firstInterval,infiniteRebirth]) //总的动作队列
        run(totalQueue, withKey: "infiniteMake")
    }
    /**
     * 停止生成障碍
     */
    func stopMakeBarrier(){
        removeAction(forKey: "infiniteMake")
        gameNode.enumerateChildNodes(withName: "topBarrier") { (matchingUnit, _) in
            matchingUnit.removeAllActions()
        }
        gameNode.enumerateChildNodes(withName: "bottomBarrie") { (matchingUnit, _) in
            matchingUnit.removeAllActions()
        }
        
    }
}

//MARK: 代理方法
extension GameScene: SKPhysicsContactDelegate{
    /**
     * 代理方法,碰触到就执行
     */
    func didBegin(_ contact: SKPhysicsContact) {
        let crashObj = contact.bodyA.categoryBitMask == physicsLayer.gameUser ? contact.bodyB : contact.bodyA
        
        if(crashObj.categoryBitMask == physicsLayer.floor){
            crashFloor = true
        }
        
        if(crashObj.categoryBitMask == physicsLayer.barrier){
            crashBarrier = true
        }
        
    }
}

//MARK: 切换状态
extension GameScene{
    /**
     * 切换到显示分数
     */
    func switchShowScore(){
        currentGameState = .showScore  //显示分数状态
        gameUser.removeAllActions() //嘎啦嘎啦移除所有动作
        stopMakeBarrier()  //停止生成障碍
        settingScoreCard() //设置计分板
    }
    /**
     * 切换至新游戏
     */
    func newGame(){
        
        let newGame = GameScene.init(size: size)  //新的游戏场景
        let switcherAnimation = SKTransition.fade(with: SKColor.black, duration: 0.05)  //切换动画
        view?.presentScene(newGame, transition: switcherAnimation)
        
    }
    /**
     * 切换至结束状态
     */
    func switchGameOverState(){
        currentGameState = .gameOver
    }
    /**
     * 切换到游戏
     */
    func switchPlayingState (){
        currentGameState = .playing
        gameNode.enumerateChildNodes(withName: "course") { (matchingUnit, _) in
            matchingUnit.run(SKAction.sequence([
                SKAction.removeFromParent(),
                SKAction.fadeOut(withDuration: 0.05)
                ]))
        }
        infiniteMakeBarrier()   //无限重生障碍
        birdFly() //跳一下
    }
    /**
     * 切换到跌落状态
     */
    func switchFallState(){
        //跌落
        currentGameState = .fall
        gameUser.removeAllActions() //去除嘎啦嘎啦的所有动作
        stopMakeBarrier()   //停止生成障碍
        
    }
    /**
     * 切换到主菜单
     */
    func switchMainMenu(){
        currentGameState = .mainMenu
        settingUpBackGround()  //设置背景
        settingForeGround()    //设置前景
        settingGameUser()  //设置游戏主角(嘎啦嘎啦)
        settingMainMenu() //设置主菜单UI
    }
    /**
     * 切换到游戏教程状态
     */
    func switchCourseState(){
        currentGameState = .course
        gameNode.enumerateChildNodes(withName: "MainMenu") { (matchingUnit, _) in
            matchingUnit.run(SKAction.sequence([
                SKAction.removeFromParent(),
                SKAction.fadeOut(withDuration: 0.05)
                ]))
        }
        settingScoreLabel()  //设置计分板
        settingCourse() //设置教程UI
        
    }
}

