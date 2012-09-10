<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Statistics Analysis'=>array('index'),
		'Show problems',
		//依据paper要求显示题目列表，或者显示全部题目
);

$this->menu=array(
//		array('label'=>TestOnlineModule::t('core','Statistics Analysis of Questions'), 'url'=>array('showprob&id=')),
	array('label'=>TestOnlineModule::t('core','Statistics Analysis of Paper'), 'url'=>array('showpaper')),
//	array('label'=>'显示学生分析', 'url'=>array('showstu')),
//	array('label'=>'Create statistics', 'url'=>array('create')),
//	array('label'=>'Manage statistics', 'url'=>array('admin')),
);	//用于列表显示内容

?>
<h1>Show Problems</h1>

<?php
//    echo "aaa";
//    $this->addProb(1127, 'T'); 
?>

<?php
    $tpaperid = $_GET['id'];
    $res = array();
    $res['0'] = 0;
    $res['1'] = 0;
    $res['2'] = 0;
    $res['3'] = 0;
    $res['4'] = 0;
    
    if ($tpaperid != "") {
    	// 分析试卷情况，分数分布情况
    	$arrays = StatisticsController::getAllGrades($tpaperid);
        foreach ($arrays as $key => $value) {
        //    echo $key;
	    //    echo "Key: $key; Value: $value<br />\n";
	        if ((int)$value < 60) $res['0']=$res['0']+1; else 
	        if ((int)$value < 70) $res['1']=$res['1']+1; else
	        if ((int)$value < 80) $res['2']=$res['2']+1; else
	        if ((int)$value < 90) $res['3']=$res['3']+1; else
	        if ((int)$value <= 100) $res['4']=$res['4']+1; 
        }
        
        // 绘制成绩分布情况折线（饼状）图
	        $this ->Widget('ext.highcharts.HighchartsWidget', array(
	       'options' => array(
	           'title' => array('text' => '分数分布情况'),
	           'xAxis' => array(
	               'categories' => array(
	                   '0~60', '60~70', '70~80', '80~90', '90~100',
	               ),
	               'labels' => array(
	                   
	                   'align' => 'right',
	                   'style' => array(
	                       'font' => 'normal 13px Verdana, sans-serif',
	               )),
	           ),
	           'yAxis' => array(
	               'min' => 0,
	               'title' => array('text' => '人数')
	           ),
	           'legend' => array(
	               'enabled' => false,
	           ),
	           'tooltip' => array(
	               'formatter' => 'js:function() {
	           return \'<STRONG>\'+ this.x +\'</STRONG>\'+
	               \': \'+this.y +
	               \'\';
	
	     }' ),
	           'series' => array(
	               array(
	                   'type' => 'column', // 这里改成pie就是饼图了，学姐看怎么好看吧
	                   'data' => $res,
	                   'dataLabels' => array(
	                       'enabled' => true,
	                       'color' => '#FFFFFF',
	                       'align' => 'center',
	                       'x' => 0,
	                       'y' => 20,
	                       'formatter' => 'js:function() {
	                        return this.y;
	                        }',
	                       'style' => array(
	                           'font' => 'normal 13px Verdana, sans-serif',
	                       ),
	                   ),
	               ),
	           )
	       )
	   ));
    }
    // 显示试卷列表
    $this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'question-bank-grid',
	'dataProvider'=>TestInfoComponent::getQuestionByPaper($_GET['id']),
	'filter'=>QuestionBank::model(),

	'columns'=>array(
		'id',
		'question',
		'selection_a',
		'selection_b',
		'selection_c',
		'selection_d',
		'type',
		'answer',
		//"ids"=>Statistics::model()->findAllByAttributes(array("pro_id"=>$data->id)),
	
			array('class'=>'CButtonColumn', 'template'=>'{view}',
				
					'buttons'=>array(
						'view' => array(
								'url'=>'Yii::app()->createUrl("testOnline/statistics/view", array("id"=>end(CHtml::listData(Statistics::model()->findAllByAttributes(array("pro_id"=>$data->id)),"id","id")), "answer"=>$data->answer))',
						),
					)
			),
	),
)); ?>

<?php 
    /*$this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'statistics-grid',
	'dataProvider'=>$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'pro_id',
		'a',
		'b',
		'c',
		'd',
		array('class'=>'CButtonColumn', 'template'=>'{view}'),
	),
)); */?>