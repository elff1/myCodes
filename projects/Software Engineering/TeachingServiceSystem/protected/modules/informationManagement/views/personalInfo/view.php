<?php
$this->breadcrumbs=array(
	InformationManagementModule::t('personalInfo','Personal Infos')=>array('index'),
	$model->id,
);
//右侧菜单栏
$this->menu=array(
	array('label'=>InformationManagementModule::t('personalInfo','List Personal Info'), 'url'=>array('index')),
	array('label'=>InformationManagementModule::t('personalInfo','Create Personal Info'), 'url'=>array('create')),
	array('label'=>InformationManagementModule::t('personalInfo','Update Personal Info'), 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>InformationManagementModule::t('personalInfo','Delete Personal Info'), 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>InformationManagementModule::t('personalInfo','Manage Personal Info'), 'url'=>array('admin')),
);
?>

<h1>View PersonalInfo #<?php echo $model->id; ?></h1>

<?php  
//显示数据表格的widget
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'first_name',
		'last_name',
		'sex',
		//'photo',
		
		array(
			'name'=>'photo',
			'type'=>'image',
			'value'=>empty($model->photo)?null:PersonalInfo::model()->imageUrl.'/'.$model->photo,
		),
		
		'date_of_birth',
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
	),
)); ?>
