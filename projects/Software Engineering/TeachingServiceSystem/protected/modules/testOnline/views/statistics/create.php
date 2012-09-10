<?php
$this->breadcrumbs=array(
  'OnlineTest Subsystem'=>array('/testOnline'),
	'Statistics'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>'显示题目分析', 'url'=>array('showprob&id=')),
	array('label'=>'显示试卷分析', 'url'=>array('showpaper')),
	array('label'=>'显示学生分析', 'url'=>array('showstu')),
	array('label'=>'Create statistics', 'url'=>array('create')),
	array('label'=>'Manage statistics', 'url'=>array('admin')),);
?>

<h1>Create statistics</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>