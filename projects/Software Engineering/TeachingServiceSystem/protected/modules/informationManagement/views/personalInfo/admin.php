<?php
//顶部导航栏
$this->breadcrumbs=array(
	InformationManagementModule::t('personalInfo','Personal Infos')=>array('index'),
	InformationManagementModule::t('personalInfo','Manage Personal Info'),
);

//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('personalInfo','List Personal Info'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('personalInfo','Create Personal Info'), 'url'=>array('create')),
);

//高级搜索控件
Yii::app()->clientScript->registerScript('search', "
$('.search-button').click(function(){
	$('.search-form').toggle();
	return false;
});
$('.search-form form').submit(function(){
	$.fn.yiiGridView.update('personal-info-grid', {
		data: $(this).serialize()
	});
	return false;
});
");
?>

<?php echo "<h1>" . InformationManagementModule::t('personalInfo','Manage Personal Info') . "</h1>"; ?>

<p class="note"><?php
	echo InformationManagementModule::t('other','You may optionally enter a comparison operator (<b>&lt;</b>, <b>&lt;=</b>, <b>&gt;</b>, <b>&gt;=</b>, <b>&lt;&gt;</b> or <b>=</b>) at the beginning of each of your search values to specify how the comparison should be done.'); /* no CHtml::encode here*/?></p>

<?php echo CHtml::link(InformationManagementModule::t('personalInfo','Advanced Search'),'#',array('class'=>'search-button')); ?>
<div class="search-form" style="display:none">
<?php $this->renderPartial('_search',array(
	'model'=>$model,
)); ?>
</div><!-- search-form -->

<!--显示数据表格的控件-->
<?php $this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'personal-info-grid',
	'dataProvider'=>$model->search(),
	'filter'=>$model,
	'columns'=>array(
		'id',
		'first_name',
		'last_name',
		'sex',
		'photo',
		'date_of_birth',
		/*
		'ethnic_group',
		'political_status',
		'birth_place_city',
		'birth_place_province',
		'original_residence_city',
		'original_residence_province',
		'home_address',
		'home_postcode',
		'home_phone',
		'email',
		'phone',
		'identity_card_number',
		*/
		array(
			'class'=>'CButtonColumn',
		),
	),
)); ?>
