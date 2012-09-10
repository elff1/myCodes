<?php
// the breadcrumbs list
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('index'),
		'PaperBank Manage',
);

// the menu list
$this->menu=array(
	array('label'=>'List PaperBank', 'url'=>array('index')),
	array('label'=>TestOnlineModule::t('core','Generate Paper'), 'url'=>array('create')),
);

// the search javascript function
Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('paper-bank-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<!-- the title -->
<h1>Manage Paper Banks</h1>

<p>
You may optionally enter a comparison operator (<b>&lt;</b>, <b>&lt;=</b>, <b>&gt;</b>, <b>&gt;=</b>, <b>&lt;&gt;</b>
or <b>=</b>) at the beginning of each of your search values to specify how the comparison should be done.
</p>

<!-- the search buttion -->
<?php echo CHtml::link('Advanced Search','#',array('class'=>'search-button')); ?>
<div class="search-form" style="display:none">
<?php $this->renderPartial('_search',array(
	'model'=>$model,
)); ?>
</div><!-- search-form -->

<!-- the course's paper list grid view -->
<?php $this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'paper-bank-grid',
	'dataProvider'=>PaperBankController::getPapers(), //$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'id',
	//	'teacher_id',
	//	'course_id',
		'is_publish',
		'timelimit',
		array(
			'class'=>'CButtonColumn',
			'buttons'=>array(
						'view' => array(
								'url'=>'Yii::app()->createUrl("testOnline/default/updateSelectedPaper",array("paper_id"=>$data->id))',
						),
			)
		),
	),
)); ?>
