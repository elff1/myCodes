<?php
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		'Statistics Analysis'=>array('index'),
		'Show problems'=>array('showprob&id='),
		'Problem#'.$model->pro_id,
		//用于显示已经做了的题目分析页面
);

$this->menu=array(
		array('label'=>TestOnlineModule::t('core','Statistics Analysis of Questions'), 'url'=>array('showprob&id=')),
		array('label'=>TestOnlineModule::t('core','Statistics Analysis of Paper'), 'url'=>array('showpaper')),
//	array('label'=>'显示学生分析', 'url'=>array('showstu')),
//	array('label'=>'Create statistics', 'url'=>array('create')),
//	array('label'=>'Manage statistics', 'url'=>array('admin')),
);	//用于列表显示内容
?>

<h1>Problem #<?php echo $model->pro_id; ?></h1>

<?php 
$ans = $_GET['answer'];
$hav = 0;
if ($ans == 'A' || $ans == 'T') $hav = $model->a;
if ($ans == 'B' || $ans == 'F') $hav = $model->b;
if ($ans == 'C') $hav = $model->c;
if ($ans == 'D') $hav = $model->d;
$hav = $hav / $model->done * 100;
?>

<?php 
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'pro_id',
		'done',
		'a',
		'b',
		'c',
		'd',
			array(
					'name'=>'anwser',
					'value'=>$ans
			),
			array(
					'name'=>'correct rate',
					'value'=>round($hav, 2)."%"
			),
	),
)); 
// 显示题目情况页面
?>

<?php 
// 绘制题目分析图像
$this ->Widget('ext.highcharts.HighchartsWidget', array(
       'options' => array(
           'title' => array('text' => 'Problem No.'.$model->pro_id),
           'xAxis' => array(
               'categories' => array(
                   'A(T)', 'B(F)', 'C', 'D', 'give up',
               ),
               'labels' => array(
                   
                   'align' => 'right',
                   'style' => array(
                       'font' => 'normal 13px Verdana, sans-serif',
               )),
           ),
           'yAxis' => array(
               'min' => 0,
               'title' => array('text' => 'number of choosing this answer')
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
                   'type' => 'column',
                   'data' => array((int)$model->a, (int)$model->b, (int)$model->c, (int)$model->d, (int)$model->done - $model->a - $model->b - $model->c - $model->d ),
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

?>
